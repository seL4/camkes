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
#include <string.h>
#include <picoserver.h>
#include <assert.h>
#include <echo_listener_common.h>

extern void *listener_send_buf;
extern void *listener_recv_buf;

seL4_CPtr listener_control_notification();

void handle_picoserver_notification(void)
{
    picoserver_event_t server_event = listener_control_event_poll();
    int ret = 0;
    int socket = 0;
    uint16_t events = 0;
    char ip_string[16] = {0};

    while (server_event.num_events_left > 0 || server_event.events) {
        socket = server_event.socket_fd;
        events = server_event.events;
        if (events & PICOSERVER_CONN) {
            picoserver_peer_t peer = listener_control_accept(socket);
            if (peer.result == -1) {
                assert(!"Failed to accept a peer");
            }
            pico_ipv4_to_string(ip_string, peer.peer_addr);
            printf("%s: Connection established with %s on socket %d\n", get_instance_name(), ip_string, socket);
        }
        if (events & PICOSERVER_READ) {
            printf("%s: Received a message on socket %d, going to print it out\n", get_instance_name(), socket);
            ret = listener_recv_recv(socket, 4096, 0);
            printf("%s", listener_recv_buf);
            memset(listener_recv_buf, 0, 4096);
        }
        if (events & PICOSERVER_CLOSE) {
            ret = listener_control_shutdown(socket, PICOSERVER_SHUT_RDWR);
            printf("%s: Connection closing on socket %d\n", get_instance_name(), socket);
        }
        if (events & PICOSERVER_FIN) {
            printf("%s: Connection closed on socket %d\n", get_instance_name(), socket);
        }
        if (events & PICOSERVER_ERR) {
            printf("%s: Error with socket %d, going to die\n", get_instance_name(), socket);
            assert(0);
        }
        server_event = listener_control_event_poll();
    }
}

int run(void)
{
    printf("%s instance starting up, going to be listening on %s:%d\n",
           get_instance_name(), ip_addr, LISTENER_PORT);

    int socket = listener_control_open(false);
    if (socket == -1) {
        assert(!"Failed to open a socket for listening!");
    }

    int ret = listener_control_bind(socket, PICOSERVER_ANY_ADDR_IPV4, LISTENER_PORT);
    if (ret) {
        assert(!"Failed to bind a socket for listening!");
    }

    ret = listener_control_listen(socket, 1);
    if (ret) {
        assert(!"Failed to listen for incoming connections!");
    }

    /* Now poll for events and handle them */
    seL4_Word badge;

    while (1) {
        seL4_Wait(listener_control_notification(), &badge);
        handle_picoserver_notification();
    }
}
