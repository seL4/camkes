/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <arpa/inet.h>
#include <string.h>

#include "client.h"

/* Benchmark utilization TCP handler */
int utiliz_socket;
int peer_socket = -1;

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

void handle_tcp_utiliz_notification(uint16_t events, int socket)
{
    int ret = 0;
    char ip_string[16] = {0};

    if (events & PICOSERVER_CONN) {
        picoserver_peer_t peer = echo_control_accept(socket);
        if (peer.result == -1) {
            ZF_LOGF("Failed to accept a peer");
        }
        peer_socket = peer.socket;
        inet_ntop(AF_INET, &peer.peer_addr, ip_string, 16);
        printf("%s: Connection established with %s on socket %d\n", get_instance_name(), ip_string, socket);

        memcpy(echo_send_buf, WHOAMI, strlen(WHOAMI));
        echo_send_send(peer_socket, strlen(WHOAMI), 0);
    }

    if (events & PICOSERVER_READ) {
        ret = echo_recv_recv(socket, 0x1000, 0);
        if (ret == -1) {
            printf("received -1\n");
        } else if (ret == 0) {
            printf("Error\n");
        }
        if (msg_match(echo_recv_buf, HELLO)) {
            memcpy(echo_send_buf, OK_READY, strlen(OK_READY));
            echo_send_send(socket, strlen(OK_READY), 0);
        } else if (msg_match(echo_recv_buf, LOAD)) {
            memcpy(echo_send_buf, OK, strlen(OK));
            echo_send_send(socket, strlen(OK), 0);
        } else if (msg_match(echo_recv_buf, SETUP)) {
            memcpy(echo_send_buf, OK, strlen(OK));
            echo_send_send(socket, strlen(OK), 0);
        } else if (msg_match(echo_recv_buf, START)) {
            idle_start();
        } else if (msg_match(echo_recv_buf, STOP)) {
            uint64_t total, kernel, idle;
            idle_stop(&total, &kernel, &idle);
            char *util_msg;
            int len = asprintf(&util_msg, IDLE_FORMAT, idle, total);
            if (len == -1) {
                ZF_LOGE("asprintf: Failed to print string");
            } else {
                len = snprintf(echo_send_buf, 0x1000, RESPONSE, len + 1, util_msg);
                if (len == -1) {
                    ZF_LOGE("asprintf: Failed to print string");
                } else {
                    echo_send_send(socket, len, 0);
                }
                free(util_msg);
            }
            echo_control_shutdown(socket, PICOSERVER_SHUT_RDWR);
        } else if (msg_match(echo_recv_buf, QUIT)) {
        } else {
            printf("Couldn't match message: %s\n", (char *)echo_recv_buf);
        }

    }

    if (events & PICOSERVER_CLOSE) {
        ret = echo_control_shutdown(socket, PICOSERVER_SHUT_RDWR);
        printf("%s: Connection closing on socket %d\n", get_instance_name(), socket);
    }
    if (events & PICOSERVER_FIN) {
        printf("%s: Connection closed on socket %d\n", get_instance_name(), socket);
        peer_socket = -1;
    }
    if (events & PICOSERVER_ERR) {
        printf("%s: Error with socket %d, going to die\n", get_instance_name(), socket);
    }
}


static int setup_utilization_socket(ps_io_ops_t *io_ops)
{
    utiliz_socket = echo_control_open(false);
    if (utiliz_socket == -1) {
        ZF_LOGE("Failed to open a socket for listening!");
        return -1;
    }

    int ret = echo_control_bind(utiliz_socket, PICOSERVER_ANY_ADDR_IPV4, UTILIZATION_PORT);
    if (ret) {
        ZF_LOGE("Failed to bind a socket for listening!");
        return ret;
    }

    ret = echo_control_listen(utiliz_socket, 1);
    if (ret) {
        ZF_LOGE("Failed to listen for incoming connections!");
        return ret;
    }

    return 0;

}

CAMKES_POST_INIT_MODULE_DEFINE(setup_utiliz, setup_utilization_socket);
