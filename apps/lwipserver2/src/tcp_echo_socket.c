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

#include <lwip/ip.h>
#include <lwip/pbuf.h>
#include <lwip/tcp.h>

#include "ports.h"
#include <echo/tuning_params.h>

typedef struct pbuf_chain {
    struct pbuf *p;
    u16_t packet_pointer; /* 'File' pointer of a pbuf */
    struct pbuf_chain *next;
} pbuf_chain_t;

typedef struct tcp_client {
    pbuf_chain_t *pbufs;
    pbuf_chain_t *pbuf_tail;
} tcp_client_t;

static tcp_client_t tcp_clients[MAX_TCP_CLIENTS];

static struct tcp_pcb *tcp_main_socket;

static struct tcp_pcb *tcp_peer_sockets[MAX_TCP_CLIENTS];

static char data_packet[0x1000] ALIGN(0x1000);

static ps_io_ops_t *ops;

static int peer_id;

static int get_free_peer_id(void)
{
    int ret = peer_id;
    peer_id = (peer_id + 1) % MAX_TCP_CLIENTS;
    return ret;
    /*
    for (int i = 0; i < MAX_TCP_CLIENTS; i++) {
        if (tcp_peer_sockets[i] == NULL) {
            return i;
        }
    }
    */
    return -1;
}

static void pop_pbuf_from_chain(int client_id)
{
    pbuf_chain_t *head = tcp_clients[client_id].pbufs;
    tcp_clients[client_id].pbufs = head->next;
    if (head->next == NULL) {
        tcp_clients[client_id].pbuf_tail = NULL;
    }
    pbuf_free(head->p);
    ZF_LOGF_IF(ps_free(&ops->malloc_ops, sizeof(*head), head),
               "Failed to free a pbuf_chain_t node");
}

static err_t lwip_sent_callback(void *arg, struct tcp_pcb *pcb, u16_t len)
{
    int client_id = (int) (uintptr_t) arg;
    u16_t can_send = MIN(tcp_sndbuf(pcb), 0x1000);

    if (tcp_clients[client_id].pbufs) {
        u16_t num_sent = 0;
        pbuf_chain_t *curr_pbuf = tcp_clients[client_id].pbufs;
        pbuf_chain_t *prev_pbuf = NULL;
        while (num_sent < can_send && curr_pbuf != NULL) {
            u16_t to_send = MIN(curr_pbuf->p->tot_len - curr_pbuf->packet_pointer,
                                can_send - num_sent);
            u16_t num_copied = pbuf_copy_partial(curr_pbuf->p, data_packet, to_send,
                                                 curr_pbuf->packet_pointer);
            err_t error = tcp_write(pcb, data_packet, num_copied, TCP_WRITE_FLAG_COPY);
            u16_t sent = num_copied;
            if (error != ERR_OK) {
                if (error != ERR_MEM) {
                    ZF_LOGF("Failed to send data through TCP socket, error = %hhd", error);
                }
                sent = 0;
            }
            prev_pbuf = curr_pbuf;
            curr_pbuf = curr_pbuf->next;
            if ((sent + prev_pbuf->packet_pointer) < prev_pbuf->p->tot_len) {
                prev_pbuf->packet_pointer += sent;
            } else {
                ZF_LOGF_IF(prev_pbuf->packet_pointer + sent != prev_pbuf->p->tot_len,
                           "Didn't sent all the data in the pbuf!");
                pop_pbuf_from_chain(client_id);
            }
        }
    }

    return ERR_OK;
}

static int add_pbuf_to_chain(int client_id, struct pbuf *p, u16_t packet_pointer)
{
    pbuf_chain_t *new_node = NULL;
    int error = ps_calloc(&ops->malloc_ops, 1, sizeof(*new_node), (void **) &new_node);
    if (error) {
        ZF_LOGE("Failed to allocate memory for the pbuf new_node head");
        return error;
    }

    new_node->p = p;
    new_node->packet_pointer = packet_pointer;

    if (tcp_clients[client_id].pbuf_tail) {
        tcp_clients[client_id].pbuf_tail->next = new_node;
        tcp_clients[client_id].pbuf_tail = new_node;
    } else {
        tcp_clients[client_id].pbuf_tail = new_node;
        tcp_clients[client_id].pbufs = new_node;
    }

    return 0;
}

static err_t lwip_tcp_recv_callback(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
    int client_id = (int) (uintptr_t) arg;
    err_t error = ERR_OK;
    if (p == NULL) {
        printf("Connection closed on a TCP socket\n");
        error = tcp_close(pcb);
        ZF_LOGF_IF(error, "Failed to close a TCP socket");
        tcp_peer_sockets[client_id] = NULL;
        return ERR_OK;
    }

    if (err != ERR_OK) {
        ZF_LOGE("Encountered error %hhd when trying to receive TCP packet", err);
        return ERR_OK;
    }

    u16_t bytes_avail = tcp_sndbuf(pcb);
    u16_t to_send = MIN(MIN(p->tot_len, bytes_avail), 0x1000);
    pbuf_copy_partial(p, data_packet, to_send, 0);
    error = tcp_write(pcb, data_packet, to_send, TCP_WRITE_FLAG_COPY);
    u16_t sent = to_send;
    if (error != ERR_OK) {
        if (error != ERR_MEM) {
            ZF_LOGF("Failed to send data through TCP socket, error = %hhd", error);
        }
        sent = 0;
    }

    if (sent < p->tot_len) {
        /* Store the rest of pbuf in the chain */
        ZF_LOGF_IF(add_pbuf_to_chain(client_id, p, sent), "Failed to add pbuf to chain");
    } else {
        pbuf_free(p);
    }

    tcp_recved(pcb, p->tot_len);

    return ERR_OK;
}

static err_t lwip_accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err)
{
    int peer_id = get_free_peer_id();
    if (peer_id == -1) {
        ZF_LOGF("not expecting another peer");
    }

    tcp_peer_sockets[peer_id] = newpcb;

    tcp_arg(newpcb, (void *) (uintptr_t) peer_id);
    tcp_sent(newpcb, lwip_sent_callback);
    tcp_recv(newpcb, lwip_tcp_recv_callback);

    printf("Peer connected\n");

    return ERR_OK;
}

int setup_tcp_socket(ps_io_ops_t *io_ops)
{
    ops = io_ops;
    tcp_main_socket = tcp_new_ip_type(IPADDR_TYPE_V4);
    if (tcp_main_socket == NULL) {
        ZF_LOGE("Failed to open a socket for listening for and accepting clients");
        return -1;
    }
    tcp_sent(tcp_main_socket, lwip_sent_callback);
    tcp_recv(tcp_main_socket, lwip_tcp_recv_callback);
    err_t error = tcp_bind(tcp_main_socket, IP_ANY_TYPE, TCP_ECHO_PORT);
    if (error) {
        ZF_LOGE("Failed to bind the TCP socket");
        return -1;
    }
    tcp_main_socket = tcp_listen_with_backlog_and_err(tcp_main_socket, MAX_TCP_CLIENTS, &error);
    if (error != ERR_OK) {
        ZF_LOGE("Failed to listen on the TCP socket");
    }
    tcp_accept(tcp_main_socket, lwip_accept_callback);
    return 0;
}

CAMKES_POST_INIT_MODULE_DEFINE(setup_tcp_socket_, setup_tcp_socket);
