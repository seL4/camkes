/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _SOCKET_
#define _SOCKET_

#include <platsupport/sync/spinlock.h>

typedef struct {
    sync_spinlock_t lock;
    int full;
    char data[100];
} socket_t;

#endif
