/*
 * Copyright 2019, Data61
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
