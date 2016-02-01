/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
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
