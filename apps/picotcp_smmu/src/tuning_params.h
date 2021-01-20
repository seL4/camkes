/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

/* Number of buffers used for sending and receiving ethernet frames. */
#define TX_BUFS 510
#define RX_BUFS 510

/* Size used for ethernet buffers */
#define BUF_SIZE 2048

/* Max size of UDP socket reads */
#define UDP_READ_SIZE 1400

/* DMA memory to use for descriptor rings */
#define DMA_RING_ALLOC_SIZE 0x4000

/* Total DMA memory to allocate */
#define DMA_ALLOC_SIZE (DMA_RING_ALLOC_SIZE + BUF_SIZE * (TX_BUFS + RX_BUFS))

/* Heap size */
#define HEAP_SIZE 0x800000
