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

static void event_callback(void *_ UNUSED) {
	printf("%s: Got an event\n", __func__);

	printf("%s: Register for another event\n", __func__);
	ev_reg_callback(&event_callback, NULL);
}

int run(void) {
	printf("Waiting for an event\n");

	ev_reg_callback(event_callback, NULL);
    return 0;
}
