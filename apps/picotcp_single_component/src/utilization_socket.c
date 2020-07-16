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
#include <ethdrivers/raw.h>

#undef PACKED
#include <pico_stack.h>
#include <pico_socket.h>
#include <pico_ipv4.h>

#include "ports.h"
#include "tuning_params.h"

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
                   Content-length: %d\n
                   ${content}\n
 * - Server closes socket.
 *
 * It is also possible for client to send QUIT\n during operation.
 *
 * The server starts recording utilization stats when it receives START and
 * finishes recording when it receives STOP.
 *
 * Only one client can be connected.
 */

struct pico_socket *utiliz_socket;
char utilz_mesg[0x1000] ALIGN(0x1000);
#define WHOAMI "100 IPBENCH V1.0\n"
#define HELLO "HELLO\n"
#define OK_READY "200 OK (Ready to go)\n"
#define LOAD "LOAD cpu_target_lukem\n"
#define OK "200 OK\n"
#define SETUP "SETUP args::\"\"\n"
#define START "START\n"
#define STOP "STOP\n"
#define QUIT "QUIT\n"
#define RESPONSE "220 VALID DATA (Data to follow)\n" \
                 "Content-length: %d\n" \
                 "%s\n"
#define IDLE_FORMAT ",%ld,%ld"
#define msg_match(msg, match) (strncmp(msg, match, strlen(match))==0)

/* Event handler for ipbench utilization test */
void handle_tcp_utiliz_notification(uint16_t events, struct pico_socket *s)
{
    int ret = 0;
    char ip_string[16] = {0};

    if (events & PICO_SOCK_EV_CONN) {
        uint32_t peer_addr;
        uint16_t remote_port;
        struct pico_socket *util = pico_socket_accept(s, &peer_addr, &remote_port);
        if (util == NULL) {
            ZF_LOGE("error\n");
        }
        pico_ipv4_to_string(ip_string, peer_addr);
        printf("%s: Connection established with %s on socket %p\n", get_instance_name(), ip_string, util);
        pico_socket_send(util, WHOAMI, strlen(WHOAMI));
    }

    if (events & PICO_SOCK_EV_RD) {
        ret = pico_socket_recv(s, utilz_mesg, 0x1000);
        if (ret == -1) {
            printf("received -1\n");
        } else if (ret == 0) {
            printf("Error\n");
        }
        if (msg_match(utilz_mesg, HELLO)) {
            pico_socket_send(s, OK_READY, strlen(OK_READY));
        } else if (msg_match(utilz_mesg, LOAD)) {
            pico_socket_send(s, OK, strlen(OK));
        } else if (msg_match(utilz_mesg, SETUP)) {
            pico_socket_send(s, OK, strlen(OK));
        } else if (msg_match(utilz_mesg, START)) {
            idle_start();
        } else if (msg_match(utilz_mesg, STOP)) {
            uint64_t total, kernel, idle;
            idle_stop(&total, &kernel, &idle);
            char *util_msg;
            int len = asprintf(&util_msg, IDLE_FORMAT, idle, total);
            if (len == -1) {
                ZF_LOGE("asprintf: Failed to print string");
            } else {
                char *response;
                len = asprintf(&response, RESPONSE, len + 1, util_msg);
                if (len == -1) {
                    ZF_LOGE("asprintf: Failed to print string");
                } else {
                    pico_socket_send(s, response, len);
                    free(response);
                }
                free(util_msg);
            }
            pico_socket_shutdown(s, PICO_SHUT_RDWR);
        } else if (msg_match(utilz_mesg, QUIT)) {
        } else {
            printf("Couldn't match message: %s\n", utilz_mesg);
        }
    }

    if (events & PICO_SOCK_EV_CLOSE) {
        ret = pico_socket_shutdown(s, PICO_SHUT_RDWR);
        printf("%s: Connection closing on socket %p\n", get_instance_name(), s);
    }
    if (events & PICO_SOCK_EV_FIN) {
        printf("%s: Connection closed on socket %p\n", get_instance_name(), s);
    }
    if (events & PICO_SOCK_EV_ERR) {
        printf("%s: Error with socket %p, going to die\n", get_instance_name(), s);
    }
}

int setup_utilization_socket(UNUSED ps_io_ops_t *io_ops)
{

    utiliz_socket = pico_socket_open(PICO_PROTO_IPV4, PICO_PROTO_TCP, handle_tcp_utiliz_notification);
    if (utiliz_socket == NULL) {
        ZF_LOGE("Failed to open a socket for listening!");
        return -1;
    }

    uint32_t local_addr = PICO_IPV4_INADDR_ANY;
    uint16_t port = short_be(UTILIZATION_PORT);
    int ret = pico_socket_bind(utiliz_socket, &local_addr, &port);
    if (ret) {
        ZF_LOGE("Failed to bind a socket for listening: %d!", pico_err);
        return -1;
    } else {
        printf("Bound to addr: %d, port %d\n", local_addr, port);
    }

    ret = pico_socket_listen(utiliz_socket, 1);
    if (ret) {
        ZF_LOGE("Failed to listen for incoming connections!");
        return -1;
    }
    return 0;

}

CAMKES_POST_INIT_MODULE_DEFINE(setup_utilization_socket_, setup_utilization_socket);
