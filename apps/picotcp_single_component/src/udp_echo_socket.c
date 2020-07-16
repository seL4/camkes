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

/* This file implements a UDP echo server that responds to every UDP packet sent
 * to it by replying with the same message to the sender. It communicates using
 * a single socket.
 *
 * If packets can't be sent then the server will stop receiving packets until it
 * is able to send.
 */

/* Buffer for receiving packets */
static char udp_data_packet[0x1000] ALIGN(0x1000);

/* If a packet is pending to be sent, this will have a length. Otherwise -1. */
static int pending_len = -1;

/* Originating IPv4 address of received packets. */
static uint32_t udp_orig;
/* Originating port of received packets */
static uint16_t udp_remote_port;
/* How many received packet events have been received while blocked for sending. */
static uint64_t rx_queued = 0;

/**
 * @brief      picotcp socket callback function
 *
 * This callback is called whenever the UDP socket has an event. We either receive
 * Read/Write/Error events.
 *
 * @param[in]  events  The events
 * @param      s       socket that the events are received on.
 */
void handle_udp_picoserver_notification(uint16_t events, struct pico_socket *s)
{
    int ret = 0;
    /* If a recieved event, add to the rx_queued amount */
    if (events & PICO_SOCK_EV_RD) {
        rx_queued++;
        events &= ~PICO_SOCK_EV_RD;
    }
    if (events & PICO_SOCK_EV_ERR) {
        printf("Error with socket %p\n", s);
    }
    /* If a write succeeded event and we have pending sends, try and resend */
    if ((events & PICO_SOCK_EV_WR) && pending_len != -1) {
        int inner_ret = pico_socket_sendto(s, udp_data_packet, pending_len, &udp_orig, udp_remote_port);
        if (inner_ret == -1) {
            ZF_LOGE("pico_socket_sendto: Send received error: %d", pico_err);
            return;
        }
        if (inner_ret == 0) {
            /* Return if packets still blocked */
            return;
        }
        pending_len = -1;
    }

    /* Try and receive available packets */
    while (rx_queued > 0) {
        ret = pico_socket_recvfrom(s, udp_data_packet, UDP_READ_SIZE, &udp_orig, &udp_remote_port);
        rx_queued--;
        if (ret == -1) {
            ZF_LOGE("pico_socket_recvfrom: received error: %d\n", pico_err);
            return;
        } else if (ret == 0) {
            ZF_LOGE("pico_socket_recvfrom: received empty message\n");
            return;
        }

        int inner_ret = pico_socket_sendto(s, udp_data_packet, ret, &udp_orig, udp_remote_port);
        if (inner_ret == -1) {
            ZF_LOGE("pico_socket_sendto: Send received error: %d", pico_err);
            pending_len = ret;
            return;
        }
        if (inner_ret == 0) {
            /* Socket is full */
            pending_len = ret;
            return;
        }
    }

}


int setup_udp_socket(UNUSED ps_io_ops_t *io_ops)
{

    struct pico_socket *udp_socket = pico_socket_open(PICO_PROTO_IPV4, PICO_PROTO_UDP, handle_udp_picoserver_notification);
    if (udp_socket == NULL) {
        ZF_LOGE("Failed to open a socket for listening!");
        return -1;
    }
    uint32_t local_addr = PICO_IPV4_INADDR_ANY;
    uint16_t udp_port = short_be(UDP_ECHO_PORT);
    int ret = pico_socket_bind(udp_socket, &local_addr, &udp_port);
    if (ret) {
        ZF_LOGE("Failed to bind a socket for listening: %d!", pico_err);
        return -1;
    } else {
        printf("Bound to addr: %d, port %d\n", local_addr, udp_port);
    }

    return 0;
}

CAMKES_POST_INIT_MODULE_DEFINE(setup_udp_socket_, setup_udp_socket);
