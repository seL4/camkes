/*
 * Copyright 2019, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#include <camkes.h>
#include <autoconf.h>
#include <stdio.h>
#include <picoserver.h>
#include <assert.h>
#include <echo_listener_common.h>

extern void *echo_send_buf;
extern void *echo_recv_buf;

int listener_socket = 0;

seL4_CPtr echo_control_notification();

void handle_picoserver_notification(void)
{
    picoserver_event_t server_event = echo_control_event_poll();
    int ret = 0;
    int socket = 0;
    uint16_t events = 0;
    char ip_string[16] = {0};

    while (server_event.num_events_left > 0 || server_event.events) {
        socket = server_event.socket_fd;
        events = server_event.events;
        if (events & PICOSERVER_CONN) {
            if (socket != listener_socket) {
                picoserver_peer_t peer = echo_control_accept(socket);
                if (peer.result == -1) {
                    assert(!"Failed to accept a peer");
                }
                pico_ipv4_to_string(ip_string, peer.peer_addr);
                printf("%s: Connection established with %s on socket %d\n", get_instance_name(), ip_string, socket);
            }
        }
        if (events & PICOSERVER_READ) {
            printf("%s: Received a message on socket %d, going to echo to Listener\n", get_instance_name(), socket);
            ret = echo_recv_recv(socket, 4096, 0);
            strncpy(echo_send_buf, echo_recv_buf, ret);
            ret = echo_send_send(listener_socket, strlen(echo_send_buf), 0);
            memset(echo_recv_buf, 0, 4096);
            memset(echo_send_buf, 0, 4096);
        }
        if (events & PICOSERVER_CLOSE) {
            ret = echo_control_shutdown(socket, PICOSERVER_SHUT_RDWR);
            printf("%s: Connection closing on socket %d\n", get_instance_name(), socket);
        }
        if (events & PICOSERVER_FIN) {
            printf("%s: Connection closed on socket %d\n", get_instance_name(), socket);
        }
        if (events & PICOSERVER_ERR) {
            printf("%s: Error with socket %d, going to die\n", get_instance_name(), socket);
            assert(0);
        }
        server_event = echo_control_event_poll();
    }
}

int run(void)
{
    printf("%s instance starting up, going to be listening on %s:%d\n",
           get_instance_name(), ip_addr, ECHO_PORT);

    int socket_in = echo_control_open(false);
    if (socket_in == -1) {
        assert(!"Failed to open a socket for listening!");
    }

    listener_socket = echo_control_open(false);
    if (listener_socket == -1) {
        assert(!"Failed to open a socket for echoing!");
    }

    int ret = echo_control_bind(socket_in, PICOSERVER_ANY_ADDR_IPV4, ECHO_PORT);
    if (ret) {
        assert(!"Failed to bind a socket for listening!");
    }

    ret = echo_control_listen(socket_in, 1);
    if (ret) {
        assert(!"Failed to listen for incoming connections!");
    }

    uint32_t ip = 0;
    pico_string_to_ipv4(ip_addr, &ip);
    ret = echo_control_connect(listener_socket, ip, LISTENER_PORT);
    if (ret) {
        assert(!"Failed to connect to the listener!");
    }

    /* Now poll for events and handle them */
    seL4_Word badge;

    while (1) {
        seL4_Wait(echo_control_notification(), &badge);
        handle_picoserver_notification();
    }
}
