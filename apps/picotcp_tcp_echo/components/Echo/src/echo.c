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
#include <virtqueue.h>
#include <camkes/io.h>
extern void *echo_send_buf;
extern void *echo_recv_buf;
#define ECHO_PORT 1234

#define NUM_BUFS 510
#define BUF_SIZE 2048
#define RECEIVE_LEN 1400
seL4_CPtr echo_control_notification();

bool write_pending = false;
int ret_save;
int done_save;
virtqueue_driver_t tx_virtqueue;
virtqueue_driver_t rx_virtqueue;
int num_tx;
/*
 * this represents the pool of buffers that can be used for TX,
 * this array is a sliding array in that num_tx acts a pointer to
 * separate between buffers that are in use and buffers that are
 * not in use. E.g. 'o' = free, 'x' = in use
 *  -------------------------------------
 *  | o | o | o | o | o | o | x | x | x |
 *  -------------------------------------
 *                          ^
 *                        num_tx
 */
tx_msg_t *pending_tx[NUM_BUFS];

static int handle_received(void)
{
    while (true) {

        virtqueue_ring_object_t handle;
        uint32_t sent_len;
        void *buf;
        if (virtqueue_get_used_buf(&rx_virtqueue, &handle, &sent_len) == 0) {
            break;
        } else {
            vq_flags_t flag;
            int more = virtqueue_gather_used(&rx_virtqueue, &handle, &buf, &sent_len, &flag);
            if (more == 0) {
                ZF_LOGF("pico_eth_send: Invalid virtqueue ring entry");
            }
            buf = DECODE_DMA_ADDRESS(buf);

        }
        tx_msg_t *msg = buf;
        if (msg->done_len == -1 || msg->done_len == 0) {
            msg->total_len = RECEIVE_LEN;
            msg->done_len = 0;
            virtqueue_init_ring_object(&handle);
            if (!virtqueue_add_available_buf(&rx_virtqueue, &handle, ENCODE_DMA_ADDRESS(msg), BUF_SIZE, VQ_RW)) {
                ZF_LOGF("handle_sent: Error while enqueuing available buffer, queue full");
            }

        } else {
            msg->total_len = msg->done_len;
            msg->done_len = 0;
            /* copy the packet over */

            virtqueue_init_ring_object(&handle);
            if (!virtqueue_add_available_buf(&tx_virtqueue, &handle, ENCODE_DMA_ADDRESS(msg), sizeof(*msg), VQ_RW)) {
                ZF_LOGF("pico_eth_send: Error while enqueuing available buffer, queue full");
            }

        }
    }
}

static int handle_sent(void)
{
    while (true) {
        virtqueue_ring_object_t handle;

        uint32_t len;
        if (virtqueue_get_used_buf(&tx_virtqueue, &handle, &len) == 0) {
            break;
        }
        void *buf;
        vq_flags_t flag;
        int more = virtqueue_gather_used(&tx_virtqueue, &handle, &buf, &len, &flag);
        if (more == 0) {
            ZF_LOGF("handle_sent: Invalid virtqueue ring entry");
        }
        tx_msg_t *msg = DECODE_DMA_ADDRESS(buf);
        msg->total_len = RECEIVE_LEN;
        msg->done_len = 0;
        virtqueue_init_ring_object(&handle);
        if (!virtqueue_add_available_buf(&rx_virtqueue, &handle, (void *)buf, BUF_SIZE, VQ_RW)) {
            ZF_LOGF("handle_sent: Error while enqueuing available buffer, queue full");
        }

    }

}


/* Benchmark utilization TCP handler */
int utiliz_socket;

#define WHOAMI "100 IPBENCH V1.0\n"
#define HELLO "HELLO"
#define OK_READY "200 OK (Ready to go)\n"
#define LOAD "LOAD cpu_target_lukem"
#define OK "200 OK\n"
#define SETUP "SETUP" // args::\"\""
#define START "START"
#define STOP "STOP"
#define QUIT "QUIT"
#define RESPONSE "220 VALID DATA (Data to follow)\n" \
                 "Content-length: %d\n" \
                 "%s\n"
#define IDLE_FORMAT "%0.3f"
#define msg_match(msg, match) (strncmp(msg, match, strlen(match))==0)

int peer_socket = -1;
char util_msg[10];
void handle_tcp_utiliz_notification(uint16_t events, int socket)
{
    int ret = 0;
    char ip_string[16] = {0};
    int client_id = -1;

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

            int len = snprintf(util_msg, sizeof(util_msg), IDLE_FORMAT, 1.f - ((double)idle / (double)total));
            len = snprintf(echo_send_buf, 0x1000, RESPONSE, len + 1, util_msg);
            echo_send_send(socket, len, 0);
            echo_control_shutdown(socket, PICOSERVER_SHUT_RDWR);
        } else if (msg_match(echo_recv_buf, QUIT)) {
        } else {
            printf("Couldn't match message: %s\n", echo_recv_buf);
        }

    }

    if (events & PICOSERVER_CLOSE) {
        ret = echo_control_shutdown(socket, PICOSERVER_SHUT_RDWR);
        printf("%s: Connection closing on socket %p\n", get_instance_name(), socket);
    }
    if (events & PICOSERVER_FIN) {
        printf("%s: Connection closed on socket %p\n", get_instance_name(), socket);
        peer_socket = -1;
    }
    if (events & PICOSERVER_ERR) {
        printf("%s: Error with socket %p, going to die\n", get_instance_name(), socket);
    }
}



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
        if (socket == utiliz_socket || socket == peer_socket) {
            handle_tcp_utiliz_notification(events, socket);
            server_event = echo_control_event_poll();
            continue;
        }
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

void setup_utilization_socket(int port_in)
{
    utiliz_socket = echo_control_open(false);
    if (utiliz_socket == -1) {
        ZF_LOGF("Failed to open a socket for listening!");
    }

    int ret = echo_control_bind(utiliz_socket, PICOSERVER_ANY_ADDR_IPV4, port_in);
    if (ret) {
        ZF_LOGF("Failed to bind a socket for listening!");
    }

    ret = echo_control_listen(utiliz_socket, 1);
    if (ret) {
        ZF_LOGF("Failed to listen for incoming connections!");
    }

}

ps_io_ops_t io_ops;
int run(void)
{
    seL4_Word badge;
    camkes_io_ops(&io_ops);
    char ip_string[16] = {0};
    uint32_t ip_raw = PICOSERVER_ANY_ADDR_IPV4;
    inet_ntop(AF_INET, &ip_raw, ip_string, 16);
    printf("%s instance starting up, going to be listening on %s:%d\n",
           get_instance_name(), ip_string, ECHO_PORT);

    seL4_Word tx_badge;
    seL4_Word rx_badge;
    /* Initialise read virtqueue */
    int error = camkes_virtqueue_driver_init_with_recv(&tx_virtqueue, camkes_virtqueue_get_id_from_name("echo_tx"),
                                                       NULL, &tx_badge);
    if (error) {
        ZF_LOGE("Unable to initialise serial server read virtqueue");
    }

    /* Initialise write virtqueue */
    error = camkes_virtqueue_driver_init_with_recv(&rx_virtqueue, camkes_virtqueue_get_id_from_name("echo_rx"),
                                                   NULL, &rx_badge);
    if (error) {
        ZF_LOGE("Unable to initialise serial server write virtqueue");
    }



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

    int udp_socket = echo_control_open(true);
    if (udp_socket == -1) {
        ZF_LOGF("Failed to open a socket for listening!");
    }
    ret = echo_control_set_async(udp_socket, true);
    if (ret) {
        ZF_LOGF("Failed to set a socket to async: %d!", ret);
    }

    ret = echo_control_bind(udp_socket, PICOSERVER_ANY_ADDR_IPV4, 1235);
    if (ret) {
        ZF_LOGF("Failed to bind a socket for listening: %d!", ret);
    }

    for (int i = 0; i < NUM_BUFS - 1; i++) {
        tx_msg_t *msg;
        tx_msg_t *buf = ps_dma_alloc(&io_ops.dma_manager, BUF_SIZE, 4, 1, PS_MEM_NORMAL);
        ZF_LOGF_IF(buf == NULL, "Failed to alloc");
        memset(buf, 0, BUF_SIZE);
        buf->total_len = RECEIVE_LEN;
        buf->socket_fd = udp_socket;

        virtqueue_ring_object_t handle;

        virtqueue_init_ring_object(&handle);

        if (!virtqueue_add_available_buf(&rx_virtqueue, &handle, ENCODE_DMA_ADDRESS(buf), sizeof(*buf), VQ_RW)) {
            ZF_LOGF("Error while enqueuing available buffer, queue full");
        }
    }
    rx_virtqueue.notify();

    setup_utilization_socket(1236);
    /* Now poll for events and handle them */

    while (1) {
        seL4_Wait(echo_control_notification(), &badge);
        if ((badge & tx_badge) == tx_badge) {
            handle_sent();
            handle_received();
            tx_virtqueue.notify();

        }
        if ((badge & echo_control_notification_badge()) == echo_control_notification_badge()) {
            handle_picoserver_notification();
        }
    }
}
