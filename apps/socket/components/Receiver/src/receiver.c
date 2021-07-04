/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <string.h>
#include <platsupport/sync/spinlock.h>

int run(void)
{
    const char *name = get_instance_name();

    printf("%s: Waiting for transport init...\n", name);
    setup_wait();

    printf("%s: Waiting for data...\n", name);
    int received = 0;
    while (!received) {
        sync_spinlock_lock((sync_spinlock_t *)&sock->lock);
        if (sock->full) {
            printf("%s: Received \"%s\".\n", name, sock->data);
            received = 1;
        }
        sync_spinlock_unlock((sync_spinlock_t *)&sock->lock);
    }

    printf("%s: Done.\n", name);
    return 0;
}
