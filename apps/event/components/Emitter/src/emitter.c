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
    unsigned long int ii;
    /* Give the collector a chance to register. */
    for (i = 0; i < 25; i++) {
        seL4_Yield();
    }
    ev_emit();


    printf("starting to emit a lot...\n");
    ii = 0;
    while (1) {
        ii++;
        ev_emit();

        if (ii % 10000 == 0) {
            printf("still emitting\n");
        }
    }

    return 0;
}

