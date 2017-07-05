/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#include <camkes.h>
#include <stdio.h>

static unsigned ping_count;

void p_ping(void) {
    ping_count++;
    if (ping_count == 2) {
        printf("All OK\n");
    } else if (ping_count > 2) {
        printf("FAIL\n");
    }
}
