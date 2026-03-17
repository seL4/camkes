/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <sel4/sel4.h>

int run(void)
{
    int i;

    printf("starting to emit events...\n");
    i = 0;
    while (i < 100000) {
        i++;
        ev_emit();

        if (i % 10000 == 0) {
            printf("still emitting events (%d)...\n", i);
        }
    }

    printf("done emitting events\n");

    return 0;
}
