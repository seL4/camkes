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
#include <arpa/inet.h>
#include <string.h>
#include <camkes/virtqueue.h>
#include <camkes/dataport.h>

extern void *echo_send_buf;
extern void *echo_recv_buf;
#define ECHO_PORT 1234


seL4_CPtr echo_control_notification();

bool write_pending = false;
int ret_save;
int done_save;

int handle_picoserver_notification(void)
{
    picoserver_event_t server_event = echo_control_event_poll();
    int ret = 0;
    int socket = 0;
    uint16_t events = 0;
    char ip_string[16] = {0};
    int result = 0;
    while (server_event.num_events_left > 0 || server_event.events) {
        socket = server_event.socket_fd;
        events = server_event.events;
        if (events & PICOSERVER_CONN) {
            picoserver_peer_t peer = echo_control_accept(socket);
            if (peer.result == -1) {
                assert(!"Failed to accept a peer");
            }
            inet_ntop(AF_INET, &peer.peer_addr, ip_string, 16);
            printf("%s: Connection established with %s on socket %d\n", get_instance_name(), ip_string, socket);
        }

        if (events & PICOSERVER_WRITE) {
            while (ret_save > 0) {
                int inner_ret = echo_send_send(socket, ret_save, done_save);
                if (inner_ret == -1) {
                    printf("Err: received -1 on send\n");
                    break;
                }
                if (inner_ret == 0) {
                    write_pending = true;
                    ret_save = ret_save;
                    done_save = done_save;

                    break;
                } else {
                    ret_save -= inner_ret;
                    done_save += inner_ret;
                }
            }
            if (ret_save == 0) {
                write_pending = false;
            }

        }

        if (events & PICOSERVER_READ) {
            while (!write_pending) {
                ret = echo_recv_recv(socket, 1200, 0);
                if (ret <= 0) {
                    break;
                }
                memcpy(echo_send_buf, echo_recv_buf, ret);
                int done = 0;
                while (ret > 0) {

                    int inner_ret = echo_send_send(socket, ret, done);
                    if (inner_ret == -1) {
                        printf("Err: -1 on send\n");
                        break;
                    }
                    if (inner_ret == 0) {
                        write_pending = true;
                        ret_save = ret;
                        done_save = done;
                        break;
                    } else {
                        ret -= inner_ret;
                        done += inner_ret;
                    }
                }
            }

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
    return result;
}


int run(void)
{
    seL4_Word badge;

    char ip_string[16] = {0};
    uint32_t ip_raw = PICOSERVER_ANY_ADDR_IPV4;
    inet_ntop(AF_INET, &ip_raw, ip_string, 16);
    printf("%s instance starting up, going to be listening on %s:%d\n",
           get_instance_name(), ip_string, ECHO_PORT);

    int socket_in = echo_control_open(false);
    if (socket_in == -1) {
        assert(!"Failed to open a socket for listening!");
    }

    int ret = echo_control_bind(socket_in, PICOSERVER_ANY_ADDR_IPV4, ECHO_PORT);
    if (ret) {
        assert(!"Failed to bind a socket for listening!");
    }

    ret = echo_control_listen(socket_in, 1);
    if (ret) {
        assert(!"Failed to listen for incoming connections!");
    }

    /* Now poll for events and handle them */

    while (1) {
        seL4_Wait(echo_control_notification(), &badge);
        int processed;
        do {
            processed = handle_picoserver_notification();
        } while (processed);
    }
}
