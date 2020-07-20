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

#include <arpa/inet.h>
#include <string.h>

#include "client.h"

#define PRINT_RECEIVE_PACKET_IDS 0
#if PRINT_RECEIVE_PACKET_IDS
static uint64_t received_len;
#endif

static int num_rx_bufs = 0;
static tx_msg_t *rx_buf_pool[NUM_TCP_BUFS];


int socket_in;
int tcp_echo_client;

int tcp_socket_handle_async_received(tx_msg_t *msg)
{
    virtqueue_ring_object_t handle;
    if (msg->socket_fd != tcp_echo_client) {
        // socket has been closed
        if (tcp_echo_client == -1) {
            rx_buf_pool[num_rx_bufs] = msg;
            num_rx_bufs++;
            return 0;
        } else {
            msg->socket_fd = tcp_echo_client;
            msg->done_len = -1;
        }

    }
    if (msg->done_len == -1 || msg->done_len == 0) {
        msg->total_len = TCP_READ_SIZE;
        msg->done_len = 0;
        virtqueue_init_ring_object(&handle);
        if (!virtqueue_add_available_buf(&rx_virtqueue, &handle, ENCODE_DMA_ADDRESS(msg), BUF_SIZE, VQ_RW)) {
            ZF_LOGF("tcp_handle_received: Error while enqueuing available buffer, queue full");
        }

    } else {
        msg->total_len = msg->done_len;
#if PRINT_RECEIVE_PACKET_IDS
        /* Because we could potentially get back less data than we asked for
         * the packet ID isn't always going to be at the start of the buffer.
         */
        if (received_len > 0) {
            if ((msg->done_len + received_len) >= TCP_READ_SIZE) {
                msg->done_len -= (TCP_READ_SIZE - received_len);
                received_len = 0;
            } else {
                received_len += msg->done_len;
                msg->done_len = 0;
            }
        }
        while (msg->done_len > 0 && received_len == 0) {
            if (msg->done_len < sizeof(uint64_t)) {
                ZF_LOGE("SPLIT ID received");
            } else {
                uint64_t sent_id = *(uint64_t *)&msg->buf[msg->total_len - msg->done_len];
                printf("ID: %ld\n", sent_id);
            }
            if (msg->done_len >= TCP_READ_SIZE) {
                msg->done_len -= TCP_READ_SIZE;
            } else {
                received_len += msg->done_len;
                msg->done_len = 0;
            }
        }
#endif
        msg->done_len = 0;
        /* copy the packet over */

        virtqueue_init_ring_object(&handle);
        if (!virtqueue_add_available_buf(&tx_virtqueue, &handle, ENCODE_DMA_ADDRESS(msg), sizeof(*msg), VQ_RW)) {
            ZF_LOGF("tcp_handle_received: Error while enqueuing available buffer, queue full");
        }

    }
    return 0;

}


int tcp_socket_handle_async_sent(tx_msg_t *msg)
{
    virtqueue_ring_object_t handle;
    msg->total_len = TCP_READ_SIZE;
    msg->done_len = 0;
    if (msg->socket_fd != tcp_echo_client) {
        if (tcp_echo_client == -1) {
            rx_buf_pool[num_rx_bufs] = msg;
            num_rx_bufs++;
            return 0;
        } else {
            msg->socket_fd = tcp_echo_client;
        }

    }
    virtqueue_init_ring_object(&handle);
    if (!virtqueue_add_available_buf(&rx_virtqueue, &handle, ENCODE_DMA_ADDRESS(msg), BUF_SIZE, VQ_RW)) {
        ZF_LOGF("tcp_handle_sent: Error while enqueuing available buffer, queue full");
    }
    return 0;

}

void handle_tcp_echo_notification(uint16_t events, int socket)
{
    int ret = 0;
    char ip_string[16] = {0};

    if (events & PICOSERVER_CONN) {
        picoserver_peer_t peer = echo_control_accept(socket);
        if (peer.result == -1) {
            ZF_LOGF("Failed to accept a peer");
        }
        tcp_echo_client = peer.socket;
        ret = echo_control_set_async(tcp_echo_client, true);
        if (ret) {
            ZF_LOGF("Failed to set a socket to async: %d!", ret);
        }
        while (num_rx_bufs > 0) {
            virtqueue_ring_object_t handle;

            virtqueue_init_ring_object(&handle);
            num_rx_bufs--;
            tx_msg_t *buf = rx_buf_pool[num_rx_bufs];
            buf->total_len = TCP_READ_SIZE;
            buf->done_len = 0;
            buf->socket_fd = tcp_echo_client;

            if (!virtqueue_add_available_buf(&rx_virtqueue, &handle, ENCODE_DMA_ADDRESS(buf), sizeof(*buf), VQ_RW)) {
                ZF_LOGF("Error while enqueuing available buffer, queue full");
            }
        }


        inet_ntop(AF_INET, &peer.peer_addr, ip_string, 16);
        printf("%s: Connection established with %s on socket %d from socket %d\n", get_instance_name(), ip_string,
               tcp_echo_client, socket);
    }
    if (events & PICOSERVER_CLOSE) {
        ret = echo_control_shutdown(socket, PICOSERVER_SHUT_RDWR);
        printf("%s: Connection closing on socket %d\n", get_instance_name(), socket);
    }
    if (events & PICOSERVER_FIN) {
        echo_control_close(tcp_echo_client);
        tcp_echo_client = -1;
        printf("%s: Connection closed on socket %d\n", get_instance_name(), socket);
    }
    if (events & PICOSERVER_ERR) {
        ZF_LOGE("%s: Error with socket %d\n", get_instance_name(), socket);
    }
}

static int setup_tcp_echo_socket(ps_io_ops_t *io_ops)
{
    socket_in = echo_control_open(false);
    if (socket_in == -1) {
        ZF_LOGF("Failed to open a socket for listening!");
    }
    int ret = echo_control_set_async(socket_in, true);
    if (ret) {
        ZF_LOGF("Failed to set a socket to async: %d!", ret);
    }

    ret = echo_control_bind(socket_in, PICOSERVER_ANY_ADDR_IPV4, TCP_ECHO_PORT);
    if (ret) {
        ZF_LOGF("Failed to bind a socket for listening!");
    }

    ret = echo_control_listen(socket_in, 1);
    if (ret) {
        ZF_LOGF("Failed to listen for incoming connections!");
    }

    for (int i = 0; i < NUM_TCP_BUFS; i++) {
        tx_msg_t *buf = ps_dma_alloc(&io_ops->dma_manager, BUF_SIZE, 4, 1, PS_MEM_NORMAL);
        ZF_LOGF_IF(buf == NULL, "Failed to alloc");
        memset(buf, 0, BUF_SIZE);
        buf->socket_fd = -1;
        buf->client_cookie = (void *)TCP_SOCKETS_ASYNC_ID;
        rx_buf_pool[num_rx_bufs] = buf;
        num_rx_bufs++;

    }

    char ip_string[16] = {0};
    uint32_t ip_raw = PICOSERVER_ANY_ADDR_IPV4;
    inet_ntop(AF_INET, &ip_raw, ip_string, 16);
    printf("%s instance starting up, going to be listening on %s:%d\n",
           get_instance_name(), ip_string, TCP_ECHO_PORT);
    return 0;

}
CAMKES_POST_INIT_MODULE_DEFINE(setup_tcp, setup_tcp_echo_socket);
