/*
 * Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>

#include "client_events.h"

void event_handler_reply(void)
{
    notification_signal_emit();
}

void event_handler(void *data)
{
    char *data_buffer = (char *)data;
    printf("Got an event : Incoming data is %s\n", data_buffer);
    event_handler_reply();
}
