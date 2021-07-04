/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <autoconf.h>
#include <stdio.h>
#include <camkes/virtqueue.h>
#include <camkes/dataport.h>
#include <virtqueue.h>
#include <picoserver.h>

#include <assert.h>
#include "tuning_params.h"
#include "ports.h"


/* TCP connection socket handler callbacks */
void handle_tcp_utiliz_notification(uint16_t events, int socket);
void handle_tcp_echo_notification(uint16_t events, int socket);

/* Async socket completion callbacks */
int udp_socket_handle_async_received(tx_msg_t *msg);
int udp_socket_handle_async_sent(tx_msg_t *msg);
int tcp_socket_handle_async_received(tx_msg_t *msg);
int tcp_socket_handle_async_sent(tx_msg_t *msg);

static_assert(BUF_SIZE >= (sizeof(tx_msg_t) + UDP_READ_SIZE),
              "BUF_SIZE is too small to hold UDP_READ_SIZE and metadata");
static_assert(BUF_SIZE >= (sizeof(tx_msg_t) + TCP_READ_SIZE),
              "BUF_SIZE is too small to hold TCP_READ_SIZE and metadata");

/* Utilization sockets */
extern int utiliz_socket;
extern int peer_socket;

/* TCP Echo sockets */
extern int socket_in;
extern int tcp_echo_client;

/* UDP echo socket */
extern int udp_socket;


/* Transports: Shared buffer for synchronous interface and virtqueue for async */
extern void *echo_send_buf;
extern void *echo_recv_buf;
extern virtqueue_driver_t tx_virtqueue;
extern virtqueue_driver_t rx_virtqueue;

/* async virtqueue identifiers */
#define TCP_SOCKETS_ASYNC_ID 1
#define UDP_SOCKETS_ASYNC_ID 2

