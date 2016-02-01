/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#ifndef _SOCKET_
#define _SOCKET_

#include <sync/spinlock.h>

typedef struct {
    sync_spinlock_t lock;
    int full;
    char data[100];
} socket_t;

#endif
