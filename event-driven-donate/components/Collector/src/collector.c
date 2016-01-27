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
