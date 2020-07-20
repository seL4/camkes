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

#include <string.h>

#include "client.h"

int udp_socket;

int udp_socket_handle_async_received(tx_msg_t *msg)
{
    virtqueue_ring_object_t handle;
    if (msg->done_len == -1 || msg->done_len == 0) {
        msg->total_len = UDP_READ_SIZE;
        msg->done_len = 0;
        virtqueue_init_ring_object(&handle);
        if (!virtqueue_add_available_buf(&rx_virtqueue, &handle, ENCODE_DMA_ADDRESS(msg), BUF_SIZE, VQ_RW)) {
            ZF_LOGF("udp_handle_received: Error while enqueuing available buffer, queue full");
        }

    } else {
        msg->total_len = msg->done_len;
        msg->done_len = 0;
        /* copy the packet over */

        virtqueue_init_ring_object(&handle);
        if (!virtqueue_add_available_buf(&tx_virtqueue, &handle, ENCODE_DMA_ADDRESS(msg), sizeof(*msg), VQ_RW)) {
            ZF_LOGF("udp_handle_received: Error while enqueuing available buffer, queue full");
        }

    }
    return 0;

}


int udp_socket_handle_async_sent(tx_msg_t *msg)
{
    virtqueue_ring_object_t handle;
    msg->total_len = UDP_READ_SIZE;
    msg->done_len = 0;
    virtqueue_init_ring_object(&handle);
    if (!virtqueue_add_available_buf(&rx_virtqueue, &handle, ENCODE_DMA_ADDRESS(msg), BUF_SIZE, VQ_RW)) {
        ZF_LOGF("udp_handle_sent: Error while enqueuing available buffer, queue full");
    }
    return 0;

}

static int setup_udp_echo_socket(ps_io_ops_t *io_ops)
{
    udp_socket = echo_control_open(true);
    if (udp_socket == -1) {
        ZF_LOGF("Failed to open a socket for listening!");
    }
    int ret = echo_control_set_async(udp_socket, true);
    if (ret) {
        ZF_LOGF("Failed to set a socket to async: %d!", ret);
    }

    ret = echo_control_bind(udp_socket, PICOSERVER_ANY_ADDR_IPV4, UDP_ECHO_PORT);
    if (ret) {
        ZF_LOGF("Failed to bind a socket for listening: %d!", ret);
    }

    for (int i = 0; i < NUM_UDP_BUFS - 1; i++) {
        tx_msg_t *buf = ps_dma_alloc(&io_ops->dma_manager, BUF_SIZE, 4, 1, PS_MEM_NORMAL);
        ZF_LOGF_IF(buf == NULL, "Failed to alloc");
        memset(buf, 0, BUF_SIZE);
        buf->total_len = UDP_READ_SIZE;
        buf->socket_fd = udp_socket;
        buf->client_cookie = (void *)UDP_SOCKETS_ASYNC_ID;

        virtqueue_ring_object_t handle;

        virtqueue_init_ring_object(&handle);

        if (!virtqueue_add_available_buf(&rx_virtqueue, &handle, ENCODE_DMA_ADDRESS(buf), sizeof(*buf), VQ_RW)) {
            ZF_LOGF("Error while enqueuing available buffer, queue full");
        }
    }

    return 0;
}

CAMKES_POST_INIT_MODULE_DEFINE(setup_udp, setup_udp_echo_socket);
