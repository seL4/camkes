/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

/* Number of buffers to use for each echo socket */
#define NUM_UDP_BUFS 510
#define NUM_TCP_BUFS 510


/* Size of initial TCP socket reads */
#define TCP_READ_SIZE 1400

/* Max size of UDP socket reads */
#define UDP_READ_SIZE 1400

/* Size of each allocation used for each send and receive. Must be large enough
 * to hold buffer and request/result information. */
#define BUF_SIZE 2048

/* This length must be greater than NUM_UDP_BUFS + NUM_TCP_BUFS */
#define PICOTCP_SOCKET_ASYNC_QUEUE_LEN 1024
#define PICOTCP_SOCKET_ASYNC_POOL_SIZE (BUF_SIZE * PICOTCP_SOCKET_ASYNC_QUEUE_LEN)
#define PICOSERVER_HEAP_SIZE 0x800000
