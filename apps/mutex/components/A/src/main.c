/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <sel4/sel4.h>
#include <stdio.h>

int run(void)
{
    const char *name = get_instance_name();
    printf("%s: Started\n", name);

    printf("%s: Trying to acquire the lock...\n", name);
    lock_lock();
    printf("%s: Got it!\n", name);

    printf("%s: Let's do some long running calculation (or more accurately, waste time)...\n", name);
    for (int i = 0; i < 10000; i++) {
        asm volatile("");
    }

    printf("%s: Releasing the lock...\n", name);
    lock_unlock();
    printf("%s: Done; let's spin.\n", name);
    while (1);

    return 0;
}

