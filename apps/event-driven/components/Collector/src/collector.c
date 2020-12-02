/*
 * Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>

#define MAX_COUNT 100
static int count = 0;

static void event_callback(void *_ UNUSED) {

    count++;

    if (count == MAX_COUNT) {
        printf("Got %d events!\n", count);
    } else {
        ev_reg_callback(&event_callback, NULL);
    }
}

int run(void) {
    ev_reg_callback(event_callback, NULL);
    return 0;
}
