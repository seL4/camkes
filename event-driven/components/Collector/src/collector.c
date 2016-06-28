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
