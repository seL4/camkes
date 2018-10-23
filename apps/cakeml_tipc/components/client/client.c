/*
 * Copyright 2018, Data61
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
virtqueue_driver_t * send_virtqueue;
virtqueue_device_t * recv_virtqueue;

void send_payload_message(int val)
{
    payload_t data;
    data.val = val;

    volatile void *alloc_buffer = NULL;

    /* First check if there is data still waiting in the send virtqueue
     * We need to flush the virtqueue before sending data on it
     */
    int send_poll_res = virtqueue_driver_poll(send_virtqueue);
    if (send_poll_res) {
        handle_send_callback();
    }

    int err = camkes_virtqueue_buffer_alloc(send_virtqueue, &alloc_buffer, sizeof(payload_t));
    if (err) {
        ZF_LOGE("Client send buffer allocation failed");
        return;
    }

    memcpy((void *)alloc_buffer, (void *)&data, sizeof(payload_t));
    err = virtqueue_driver_enqueue(send_virtqueue,
                                   alloc_buffer, sizeof(payload_t));
    if (err != 0) {
        ZF_LOGE("Client send enqueue failed");
        camkes_virtqueue_buffer_free(send_virtqueue, alloc_buffer);
        return;
    }

    err = virtqueue_driver_signal(send_virtqueue);
    if (err != 0) {
        ZF_LOGE("Client send signal failed");
        return;
    }
}

void handle_virtqueue_message(volatile void *buffer)
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
    volatile void *available_buff = NULL;
    size_t buf_size = 0;
    int dequeue_res = virtqueue_device_dequeue(recv_virtqueue,
                                               &available_buff,
                                               &buf_size);

    /* Process the incoming virtqueue message */
    handle_virtqueue_message(available_buff);

    int enqueue_res = virtqueue_device_enqueue(recv_virtqueue, available_buff, buf_size);
    if (enqueue_res) {
        ZF_LOGE("Client recieve enqueue failed");
        return;
    }

    int err = virtqueue_device_signal(recv_virtqueue);
    if (err != 0) {
        ZF_LOGE("Client recieve signal failed");
        return;
    }
}

void handle_send_callback(void)
{
    volatile void* send_buff = NULL;
    size_t buf_size = 0;
    int err = virtqueue_driver_dequeue(send_virtqueue,
                                       &send_buff,
                                       &buf_size);
    if (err) {
        ZF_LOGE("Client send dequeue failed");
        return;
    }
    /* Clean up and free the buffer we allocated */
    camkes_virtqueue_buffer_free(send_virtqueue, send_buff);
}

void virtqueue_wait_callback(void)
{
    int err;
    int recv_poll_res = virtqueue_device_poll(recv_virtqueue);
    if (recv_poll_res) {
        handle_recv_callback();
    }
    if (recv_poll_res == -1) {
        ZF_LOGF("Client recv poll failed");
    }

    int send_poll_res = virtqueue_driver_poll(send_virtqueue);
    if (send_poll_res) {
        handle_send_callback();
    }
    if (send_poll_res == -1) {
        ZF_LOGF("Client send poll failed");
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
