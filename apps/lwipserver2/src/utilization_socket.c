/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <autoconf.h>
#include <stdbool.h>
#include <string.h>

#include <camkes.h>

#include <lwip/ip.h>
#include <lwip/pbuf.h>
#include <lwip/tcp.h>

#include "ports.h"
#include <echo/tuning_params.h>

/* This file implements a TCP based utilization measurment process that starts
 * and stops utilization measurements based on a client's requests.
 * The protocol used to communicate is as follows:
 * - Client connects
 * - Server sends: 100 IPBENCH V1.0\n
 * - Client sends: HELLO\n
 * - Server sends: 200 OK (Ready to go)\n
 * - Client sends: LOAD cpu_target_lukem\n
 * - Server sends: 200 OK\n
 * - Client sends: SETUP args::""\n
 * - Server sends: 200 OK\n
 * - Client sends: START\n
 * - Client sends: STOP\n
 * - Server sends: 220 VALID DATA (Data to follow)\n
 *                                Content-length: %d\n
 *                                ${content}\n
 * - Server closes socket.
 *
 * It is also possible for client to send QUIT\n during operation.
 *
 * The server starts recording utilization stats when it receives START and
 * finishes recording when it receives STOP.
 *
 * Only one client can be connected.
 */

static struct tcp_pcb *utiliz_socket;
static char data_packet[0x1000] ALIGN(0x1000);

#define WHOAMI "100 IPBENCH V1.0\n"
#define HELLO "HELLO\n"
#define OK_READY "200 OK (Ready to go)\n"
#define LOAD "LOAD cpu_target_lukem\n"
#define OK "200 OK\n"
#define SETUP "SETUP args::\"\"\n"
#define START "START\n"
#define STOP "STOP\n"
#define QUIT "QUIT\n"
#define RESPONSE "220 VALID DATA (Data to follow)\n"    \
    "Content-length: %d\n"                              \
    "%s\n"
#define IDLE_FORMAT ",%ld,%ld"
#define msg_match(msg, match) (strncmp(msg, match, strlen(match))==0)

static err_t utilization_sent_callback(void *arg, struct tcp_pcb *pcb, u16_t len)
{
    return ERR_OK;
}

static err_t utilization_recv_callback(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
    if (p == NULL) {
        tcp_close(pcb);
        return ERR_OK;
    }

    pbuf_copy_partial(p, data_packet, p->tot_len, 0);
    err_t error;

    if (msg_match(data_packet, HELLO)) {
        error = tcp_write(pcb, OK_READY, strlen(OK_READY), TCP_WRITE_FLAG_COPY);
        ZF_LOGF_IF(error, "Failed to send OK_READY message through utilization peer");
    } else if (msg_match(data_packet, LOAD)) {
        error = tcp_write(pcb, OK, strlen(OK), TCP_WRITE_FLAG_COPY);
        ZF_LOGF_IF(error, "Failed to send OK message through utilization peer");
    } else if (msg_match(data_packet, SETUP)) {
        error = tcp_write(pcb, OK, strlen(OK), TCP_WRITE_FLAG_COPY);
        ZF_LOGF_IF(error, "Failed to send OK message through utilization peer");
    } else if (msg_match(data_packet, START)) {
        idle_start();
    } else if (msg_match(data_packet, STOP)) {
        uint64_t total, kernel, idle;
        idle_stop(&total, &kernel, &idle);

        char *util_msg;
        int len = asprintf(&util_msg, IDLE_FORMAT, idle, total);
        if (len == -1) {
            ZF_LOGE("Failed to format the utilisation message for ipbench");
        } else {
            char *response;
            len = asprintf(&response, RESPONSE, len + 1, util_msg);
            if (len == -1) {
                ZF_LOGE("Failed to format the response message for ipbench");
            } else {
                error = tcp_write(pcb, response, len, TCP_WRITE_FLAG_COPY);
                free(response);
            }
            free(util_msg);
        }
        tcp_shutdown(pcb, 0, 1);
    } else if (msg_match(data_packet, QUIT)) {
        /* Do nothing for now */
    } else {
        printf("Received a message that we can't handle %s\n", data_packet);
    }

    return ERR_OK;
}

static err_t utilization_accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err)
{
    printf("Utilization connection established!\n");
    err_t error = tcp_write(newpcb, WHOAMI, strlen(WHOAMI), TCP_WRITE_FLAG_COPY);
    ZF_LOGF_IF(error, "Failed to send WHOAMI message through utilization peer");
    tcp_sent(newpcb, utilization_sent_callback);
    tcp_recv(newpcb, utilization_recv_callback);
    return ERR_OK;
}

int setup_utilization_socket(UNUSED ps_io_ops_t *io_ops)
{
    utiliz_socket = tcp_new_ip_type(IPADDR_TYPE_V4);
    if (utiliz_socket == NULL) {
        ZF_LOGE("Failed to open a socket for listening!");
        return -1;

    }

    err_t error = tcp_bind(utiliz_socket, IP_ANY_TYPE, UTILIZATION_PORT);
    if (error) {
        ZF_LOGE("Failed to bind the TCP socket");
        return -1;
    } else {
        printf("Utilisation port bound to port %d\n", UTILIZATION_PORT);
    }

    utiliz_socket = tcp_listen_with_backlog_and_err(utiliz_socket, 1, &error);
    if (error != ERR_OK) {
        ZF_LOGE("Failed to listen on the utilization socket");
    }
    tcp_accept(utiliz_socket, utilization_accept_callback);

    return 0;
}

CAMKES_POST_INIT_MODULE_DEFINE(setup_utilization_socket_, setup_utilization_socket);
