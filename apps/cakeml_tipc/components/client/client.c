/*
 * Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <virtqueue.h>
#include <camkes/virtqueue.h>
#include <utils/util.h>

#define COUNT_LIMIT 20

/* Message to be passed around  clients*/
typedef struct {
    int val;
} payload_t;

/* Each component has a send and recv virtqueue */
virtqueue_driver_t send_virtqueue;
virtqueue_device_t recv_virtqueue;

void handle_send_callback(void);

void send_payload_message(int val)
{
    payload_t data;
    data.val = val;

    void *alloc_buffer = NULL;

    /* First check if there is data still waiting in the send virtqueue
     * We need to flush the virtqueue before sending data on it
     */
    if (VQ_DRV_POLL(&send_virtqueue)) {
        handle_send_callback();
    }

    int err = camkes_virtqueue_buffer_alloc(&send_virtqueue, &alloc_buffer, sizeof(payload_t));
    if (err) {
        ZF_LOGE("Client send buffer allocation failed");
        return;
    }

    memcpy(alloc_buffer, (void *)&data, sizeof(payload_t));

    if (camkes_virtqueue_driver_send_buffer(&send_virtqueue, alloc_buffer, sizeof(payload_t)) != 0) {
        camkes_virtqueue_buffer_free(&send_virtqueue, alloc_buffer);
        return;
    }
    send_virtqueue.notify();
}

void handle_virtqueue_message(void *buffer)
{
    payload_t *data = (payload_t *)buffer;

    printf("Client %d recieved payload value: %d\n", client_id, data->val);

    /* Finish the message passing once we reach COUNT_LIMIT */
    if (data->val == COUNT_LIMIT) {
        return;
    }

    /* Forward the message with an incremented count */
    send_payload_message(data->val + 1);
}

void handle_recv_callback(void)
{
    void *available_buff = NULL;
    size_t buf_size = 0;
    vq_flags_t flag;
    virtqueue_ring_object_t handle;
    if (!virtqueue_get_available_buf(&recv_virtqueue, &handle)) {
        ZF_LOGE("Client virtqueue dequeue failed");
        return;
    }

    while (!camkes_virtqueue_device_gather_buffer(&recv_virtqueue, &handle, &available_buff, &buf_size, &flag)) {
        /* Process the incoming virtqueue message */
        handle_virtqueue_message(available_buff);
    }

    if (!virtqueue_add_used_buf(&recv_virtqueue, &handle, 0)) {
        ZF_LOGE("Unable to enqueue used recv buffer");
        return;
    }

    recv_virtqueue.notify();

}

void handle_send_callback(void)
{
    void *send_buff = NULL;
    size_t buf_size = 0;
    uint32_t wr_len = 0;
    vq_flags_t flag;
    virtqueue_ring_object_t handle;
    if (!virtqueue_get_used_buf(&send_virtqueue, &handle, &wr_len)) {
        ZF_LOGE("Client send dequeue failed");
        return;
    }
    while (!camkes_virtqueue_driver_gather_buffer(&send_virtqueue, &handle, &send_buff, &buf_size, &flag)) {
        /* Clean up and free the buffer we allocated */
        camkes_virtqueue_buffer_free(&send_virtqueue, send_buff);
    }
}

void virtqueue_wait_callback(void)
{
    if (VQ_DEV_POLL(&recv_virtqueue)) {
        handle_recv_callback();
    }

    if (VQ_DRV_POLL(&send_virtqueue)) {
        handle_send_callback();
    }
}

int run()
{
    /* Initialise send virtqueue */
    int err = camkes_virtqueue_driver_init(&send_virtqueue, 0);
    if (err) {
        ZF_LOGE("Unable to initialise client send virtqueue");
        return 1;
    }

    /* Initialise recv virtqueue */
    err = camkes_virtqueue_device_init(&recv_virtqueue, 1);
    if (err) {
        ZF_LOGE("Unable to initialise client recv virtqueue");
        return 1;
    }

    /* Client 0 will send the first message */
    if (client_id == 0) {
        printf("Client 0 sending first message\n");
        send_payload_message(1);
    }

    timeout_periodic(0, 1000 * NS_IN_MS);
    seL4_Word badge;
    seL4_CPtr notification = timeout_notification();
    while (1) {
        seL4_Wait(notification, &badge);
    }
}
