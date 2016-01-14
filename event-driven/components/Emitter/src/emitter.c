/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <camkes.h>
#include <stdio.h>
#include <sel4/sel4.h>

int run(void) {
    int i;
    unsigned long int ii;

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

