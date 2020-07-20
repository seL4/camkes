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


#include <assert.h>
#include <camkes/io.h>
#include "client.h"


seL4_CPtr echo_control_notification();

virtqueue_driver_t tx_virtqueue;
virtqueue_driver_t rx_virtqueue;


static void handle_picoserver_notification(UNUSED seL4_Word badge, UNUSED void *cookie)
{
    picoserver_event_t server_event = echo_control_event_poll();
    int socket = 0;
    uint16_t events = 0;
    while (server_event.num_events_left > 0 || server_event.events) {
        socket = server_event.socket_fd;
        events = server_event.events;
        if (socket == socket_in || socket == tcp_echo_client) {
            handle_tcp_echo_notification(events, socket);
            server_event = echo_control_event_poll();

        } else {
            ZF_LOGE("Got event for socket: %d but no registered handler", socket);
        }

        server_event = echo_control_event_poll();
    }
}

static tx_msg_t *get_msg_from_queue(virtqueue_driver_t *queue)
{
    virtqueue_ring_object_t handle;
    uint32_t len;
    if (virtqueue_get_used_buf(queue, &handle, &len) == 0) {
        return NULL;
    }

    vq_flags_t flag;
    void *buf;
    int more = virtqueue_gather_used(queue, &handle, &buf, &len, &flag);
    if (more == 0) {
        ZF_LOGF("Failed to dequeue message from the queue");
    }
    return DECODE_DMA_ADDRESS(buf);

}



static void async_event(UNUSED seL4_Word badge, void *cookie)
{
    while (true) {

        tx_msg_t *msg = get_msg_from_queue(&tx_virtqueue);
        if (!msg) {
            break;
        }
        if ((uintptr_t)msg->client_cookie == UDP_SOCKETS_ASYNC_ID) {
            udp_socket_handle_async_sent(msg);

        } else if ((uintptr_t)msg->client_cookie == TCP_SOCKETS_ASYNC_ID) {
            tcp_socket_handle_async_sent(msg);
        } else {
            ZF_LOGE("Message sent but bad socket: %d", msg->socket_fd);
        }
    }
    while (true) {

        tx_msg_t *msg = get_msg_from_queue(&rx_virtqueue);
        if (!msg) {
            break;
        }
        if ((uintptr_t)msg->client_cookie == UDP_SOCKETS_ASYNC_ID) {
            udp_socket_handle_async_received(msg);
        } else if ((uintptr_t)msg->client_cookie == TCP_SOCKETS_ASYNC_ID) {
            tcp_socket_handle_async_received(msg);
        } else {
            ZF_LOGE("Message received but bad socket: %d", msg->socket_fd);
        }
    }

    tx_virtqueue.notify();
}


int setup_echo_server(ps_io_ops_t *io_ops)
{
    seL4_Word tx_badge;
    seL4_Word rx_badge;
    /* Initialise read virtqueue */
    int error = camkes_virtqueue_driver_init_with_recv(&tx_virtqueue, camkes_virtqueue_get_id_from_name("echo_tx"),
                                                       NULL, &tx_badge);
    if (error) {
        ZF_LOGE("Unable to initialise TX virtqueue");
    }

    /* Initialise write virtqueue */
    error = camkes_virtqueue_driver_init_with_recv(&rx_virtqueue, camkes_virtqueue_get_id_from_name("echo_rx"),
                                                   NULL, &rx_badge);
    if (error) {
        ZF_LOGE("Unable to initialise RX virtqueue");
    }

    /* Now poll for events and handle them */
    single_threaded_component_register_handler(tx_badge, "async_notification", async_event, NULL);
    single_threaded_component_register_handler(echo_control_notification_badge(), "sync_notification",
                                               handle_picoserver_notification, NULL);
    tx_virtqueue.notify();
    return 0;
}

CAMKES_POST_INIT_MODULE_DEFINE(setup_echo, setup_echo_server);
