/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>

static void event_callback(void *_ UNUSED)
{
    printf("%s: Got an event\n", __func__);

    printf("%s: Register for another event\n", __func__);
    ev_reg_callback(&event_callback, NULL);
}

int run(void)
{
    printf("Waiting for an event\n");

    ev_reg_callback(event_callback, NULL);
    return 0;
}
