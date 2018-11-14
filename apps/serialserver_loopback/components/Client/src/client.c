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

#include <autoconf.h>
#include <camkes.h>
#include <stdio.h>
#include <virtqueue.h>
#include <camkes/virtqueue.h>
#include <utils/util.h>
#include <string.h>

virtqueue_driver_t * read_virtqueue;
virtqueue_driver_t * write_virtqueue;

void handle_read_callback(virtqueue_driver_t *vq);
void handle_write_callback(virtqueue_driver_t *vq);

void write_output(char *write_data, size_t write_data_size)
{
    volatile void *alloc_buffer = NULL;

    /* Check if there is data still waiting in the write virtqueue */
    int write_poll_res = virtqueue_driver_poll(write_virtqueue);
    if (write_poll_res) {
        handle_write_callback(write_virtqueue);
    }

    int err = camkes_virtqueue_buffer_alloc(write_virtqueue, &alloc_buffer, write_data_size);
    if (err) {
        return;
    }

    char *buffer_data = (char *)alloc_buffer;
    memcpy(buffer_data, write_data, write_data_size);

    err = virtqueue_driver_enqueue(write_virtqueue,
                                   alloc_buffer, write_data_size);
    if (err != 0) {
        ZF_LOGE("Client write enqueue failed");
        camkes_virtqueue_buffer_free(write_virtqueue, alloc_buffer);
        return;
    }

    err = virtqueue_driver_signal(write_virtqueue);
    if (err != 0) {
        ZF_LOGE("Client write signal failed");
        return;
    }

}

void loopback_test(void)
{
    volatile void *alloc_buffer = NULL;
    size_t buffer_size = 4000;

    /* Check if there is data still waiting in the write virtqueue */
    int read_poll_res = virtqueue_driver_poll(read_virtqueue);
    if (read_poll_res) {
        handle_read_callback(read_virtqueue);
    }

    int err = camkes_virtqueue_buffer_alloc(read_virtqueue, &alloc_buffer, buffer_size);
    if (err) {
        ZF_LOGE("Read buffer allocation failed");
        return;
    }

    memset(alloc_buffer, 0, buffer_size);

    err = virtqueue_driver_enqueue(read_virtqueue,
                                   alloc_buffer, buffer_size);
    if (err != 0) {
        ZF_LOGE("Client read enqueue failed");
        camkes_virtqueue_buffer_free(read_virtqueue, alloc_buffer);
        return;
    }

    err = virtqueue_driver_signal(read_virtqueue);
    if (err != 0) {
        ZF_LOGE("Client read signal failed");
        return;
    }
}

void handle_read_callback(virtqueue_driver_t *vq)
{
    volatile void* buf = NULL;
    size_t buf_size = 0;
    int err = virtqueue_driver_dequeue(vq,
                                       &buf,
                                       &buf_size);
    if (err) {
        ZF_LOGE("Client virtqueue dequeue failed");
        return;
    }

    char *read_buffer = (char *)buf;
    write_output(read_buffer, buf_size);

    /* Clean up and free the buffer we allocated */
    camkes_virtqueue_buffer_free(vq, buf);

    loopback_test();
}

void handle_write_callback(virtqueue_driver_t *vq)
{
    volatile void* buf = NULL;
    size_t buf_size = 0;
    int err = virtqueue_driver_dequeue(vq,
                                       &buf,
                                       &buf_size);
    if (err) {
        ZF_LOGE("Client virtqueue dequeue failed");
        return;
    }
    /* Clean up and free the buffer we allocated */
    camkes_virtqueue_buffer_free(vq, buf);
}


void serial_wait_callback(void)
{
    int err;
    int read_poll_res = virtqueue_driver_poll(read_virtqueue);
    if (read_poll_res) {
        handle_read_callback(read_virtqueue);
    }
    if (read_poll_res == -1) {
        ZF_LOGF("Client read poll failed");
    }

    int write_poll_res = virtqueue_driver_poll(write_virtqueue);
    if (write_poll_res) {
        handle_write_callback(write_virtqueue);
    }
    if (write_poll_res == -1) {
        ZF_LOGF("Client write poll failed");
    }
}

void pre_init(void)
{
    set_putchar(serial_putchar_putchar);
}

int run(void)
{
    ZF_LOGE("Starting loopback serial test");

    /* Initialise read virtqueue */
    int err = camkes_virtqueue_driver_init(&read_virtqueue, 0);
    if (err) {
        ZF_LOGE("Unable to initialise read virtqueue");
        return 1;
    }

    /* Initialise write virtqueue */
    err = camkes_virtqueue_driver_init(&write_virtqueue, 1);
    if (err) {
        ZF_LOGE("Unable to initialise write virtqueue");
        return 1;
    }

    loopback_test();

    return 0;
}
