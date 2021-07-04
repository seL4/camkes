/*
 * Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <autoconf.h>
#include <camkes.h>
#include <stdio.h>
#include <virtqueue.h>
#include <camkes/virtqueue.h>
#include <utils/util.h>
#include <string.h>

virtqueue_driver_t read_virtqueue;
virtqueue_driver_t write_virtqueue;

void handle_read_callback(virtqueue_driver_t *vq);
void handle_write_callback(virtqueue_driver_t *vq);

void write_output(char *write_data, size_t write_data_size)
{
    if (camkes_virtqueue_driver_scatter_send_buffer(&write_virtqueue, write_data, write_data_size)) {
        ZF_LOGE("Client write enqueue failed");
        return;
    }
    write_virtqueue.notify();
}

void loopback_test(void)
{
    size_t buffer_size = 4000;


    if (camkes_virtqueue_driver_scatter_send_buffer(&read_virtqueue, NULL, buffer_size)) {
        ZF_LOGE("Client read enqueue failed");
        return;
    }

    fflush(stdout);
    read_virtqueue.notify();
}

void handle_read_callback(virtqueue_driver_t *vq)
{
    void *buf = NULL;
    unsigned len = 0;
    virtqueue_ring_object_t handle;
    vq_flags_t flags;

    if (!virtqueue_get_used_buf(vq, &handle, &len)) {
        ZF_LOGE("Client virtqueue dequeue failed");
        return;
    }
    if (!(buf = calloc(len, sizeof(char)))) {
        ZF_LOGE("Could not allocate memory");
        return;
    }
    if (camkes_virtqueue_driver_gather_copy_buffer(vq, &handle, buf, len) != 0) {
        free(buf);
    }
    write_output(buf, len);
}

void handle_write_callback(virtqueue_driver_t *vq)
{
    void *buf = NULL;
    unsigned len = 0;
    virtqueue_ring_object_t handle;
    vq_flags_t flags;


    if (!virtqueue_get_used_buf(vq, &handle, &len)) {
        ZF_LOGE("Client virtqueue dequeue failed");
        return;
    }
    while (camkes_virtqueue_driver_gather_buffer(vq, &handle, &buf, &len, &flags) == 0) {
        /* Clean up and free the buffer we allocated */
        camkes_virtqueue_buffer_free(vq, buf);
    }
    /* Moving the call here forces synchronicity but makes it a bit slower */
    /* TODO: make it more asynchronous */
    loopback_test();
}

/*
void serial_wait_callback(void)
{
    if (VQ_DRV_POLL(&read_virtqueue)) {
        handle_read_callback(&read_virtqueue);
    }
    if (VQ_DRV_POLL(&write_virtqueue)) {
        handle_write_callback(&write_virtqueue);
    }
}
*/

void serial_read_wait_callback(void)
{
    if (VQ_DRV_POLL(&read_virtqueue)) {
        handle_read_callback(&read_virtqueue);
    }
}

void serial_write_wait_callback(void)
{
    if (VQ_DRV_POLL(&write_virtqueue)) {
        handle_write_callback(&write_virtqueue);
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
