/*
 * Copyright 2020, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#include <autoconf.h>
#include <stdbool.h>

#include <camkes.h>

#undef PACKED
#include <pico_stack.h>
#include <pico_socket.h>
#include <pico_ipv4.h>

#include "ports.h"
#include "tuning_params.h"


/* This file implements a echo server that listens on a TCP port and returns
 * every byte it receives in order. At most MAX_TCP_CLIENTS can be connected at
 * a time. If clients disconnect, more can then connect.
 *
 * The server tries to read data in chunks of TCP_READ_SIZE and then immediately
 * tries to send what was received. If sending becomes blocked then the server
 * won't try and receive new data until it has successfully sent the current
 * data.
 */

/* Socket global data */

/* TCP socket listening for clients */
static struct pico_socket *socket_in;

/* Connected client sockets */
static struct pico_socket *connected[MAX_TCP_CLIENTS];

/* Per-client buffer for receiving packets */
static char data_packet[MAX_TCP_CLIENTS][0x1000] ALIGN(0x1000);

/* Per-client state for saving a pending send */
/* Whether a write is queued */
static bool write_pending[MAX_TCP_CLIENTS];
/* Amount of data left to send in the write */
static int remaining_payload[MAX_TCP_CLIENTS];
/* Amount of data from payload sent already */
static int sent_payload[MAX_TCP_CLIENTS];


/**
 * @brief      picotcp socket callback function
 *
 * This function gets called when there are any socket events on the TCP
 * socket or any sockets created from it. It isn't possible to register
 * different handlers for the client sockets so this handler has to handle
 * both connections and sends/receives.
 *
 * @param[in]  events  The picotcp events
 * @param      s       Socket the event applies to.
 */
void handle_tcp_picoserver_notification(uint16_t events, struct pico_socket *s)
{
    int ret = 0;

    /* Detect the client based on the reference to the socket given to the callback. */
    int client_id = -1;
    if (s != socket_in) {
        for (int i = 0; i < MAX_TCP_CLIENTS; i++) {
            if (connected[i] == s) {
                client_id = i;
                break;
            }
        }
    }

    /* New client connected event */
    if (events & PICO_SOCK_EV_CONN) {
        uint32_t peer_addr;
        uint16_t remote_port;
        int connect_client_id = -1;
        assert(client_id == -1);
        /* Find a free client ID */
        for (int i = 0; i < MAX_TCP_CLIENTS; i++) {
            if (connected[i] == NULL) {
                connect_client_id = i;
                break;
            }
        }
        if (connect_client_id == -1 || connect_client_id == MAX_TCP_CLIENTS) {
            printf("Cannot connect new client\n");
        } else {
            /* Accept client connection */
            connected[connect_client_id] = pico_socket_accept(socket_in, &peer_addr, &remote_port);
            if (connected[connect_client_id] == NULL) {
                ZF_LOGE("pico_socket_accept: error received: %d", pico_err);
            }
            write_pending[connect_client_id] = false;
            char ip_string[16] = {0};
            pico_ipv4_to_string(ip_string, peer_addr);
            printf("%s: Connection established with %s on socket %p\n", get_instance_name(), ip_string, connected);
        }


    }
    /* Write successful event. If we have blocked writes try and resend */
    if (events & PICO_SOCK_EV_WR && write_pending[client_id]) {
        while (remaining_payload[client_id] > 0) {
            int inner_ret = pico_socket_send(s, data_packet[client_id] + sent_payload[client_id], remaining_payload[client_id]);
            if (inner_ret == -1) {
                /* Received socket error. report and keep going. */
                ZF_LOGE("pico_socket_send: error received: %d", pico_err);
                break;
            }
            if (inner_ret == 0) {
                write_pending[client_id] = true;
                remaining_payload[client_id] = remaining_payload[client_id];
                sent_payload[client_id] = sent_payload[client_id];

                break;
            } else {
                remaining_payload[client_id] -= inner_ret;
                sent_payload[client_id] += inner_ret;
            }
        }
        /* If we successfully sent everything, clear the write pending flag */
        if (remaining_payload[client_id] == 0) {
            write_pending[client_id] = false;
            /* Set the Read event bit in order to clear any reads that we skipped
             * while blocking for send.
             */
            events |= PICO_SOCK_EV_RD;
        }

    }

    /* Read event on client socket. Receive the data and try resend immediately. */
    if (events & PICO_SOCK_EV_RD) {
        while (!write_pending[client_id]) {
            ret = pico_socket_recv(s, data_packet[client_id], TCP_READ_SIZE);
            if (ret == -1) {
                /* Received socket error. Report and keep going. */
                ZF_LOGE("pico_socket_recv: error received: %d", pico_err);
                break;
            } else if (ret == 0) {
                /* No data available */
                break;
            }
            int done = 0;
            while (ret > 0) {
                int inner_ret = pico_socket_send(s, data_packet[client_id] + done, ret);
                if (inner_ret == -1) {
                    /* Received socket error, report and keep going. */
                    ZF_LOGE("pico_socket_send: error received: %d", pico_err);
                    break;
                }
                if (inner_ret == 0) {
                    /* Cannot send more data. Save for write-completed event to retry */
                    write_pending[client_id] = true;
                    remaining_payload[client_id] = ret;
                    sent_payload[client_id] = done;
                    break;
                } else {
                    ret -= inner_ret;
                    done += inner_ret;
                }
            }
        }

    }

    if (events & PICO_SOCK_EV_CLOSE) {
        ret = pico_socket_shutdown(s, PICO_SHUT_RDWR);
        printf("%s: Connection closing on socket %p\n", get_instance_name(), s);
    }
    if (events & PICO_SOCK_EV_FIN) {
        assert(client_id != -1);
        connected[client_id] = NULL;
        printf("%s: Connection closed on socket %p\n", get_instance_name(), s);
    }
    if (events & PICO_SOCK_EV_ERR) {
        printf("%s: Error with socket %p, going to die\n", get_instance_name(), s);
        assert(0);
    }
}


int setup_tcp_socket(UNUSED ps_io_ops_t *io_ops)
{
    socket_in = pico_socket_open(PICO_PROTO_IPV4, PICO_PROTO_TCP, handle_tcp_picoserver_notification);
    if (socket_in == NULL) {
        ZF_LOGE("Failed to open a socket for listening!");
        return -1;
    }
    uint32_t local_addr = PICO_IPV4_INADDR_ANY;
    uint16_t port = short_be(TCP_ECHO_PORT);
    int ret = pico_socket_bind(socket_in, &local_addr, &port);
    if (ret) {
        ZF_LOGE("Failed to bind a socket for listening: %d!", pico_err);
        return -1;
    } else {
        printf("Bound to addr: %d, port %d\n", local_addr, port);
    }

    ret = pico_socket_listen(socket_in, MAX_TCP_CLIENTS);
    if (ret) {
        ZF_LOGE("Failed to listen for incoming connections!");
        return -1;
    }
    return 0;
}

CAMKES_POST_INIT_MODULE_DEFINE(setup_tcp_socket_, setup_tcp_socket);
