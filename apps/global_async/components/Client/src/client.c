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
#include <camkes/dataport.h>

#include "client_events.h"

void notification_event_loop(void)
{
    seL4_CPtr event_notification = notification_ready_notification();
    while (true) {
        seL4_Word badge;
        seL4_Wait(event_notification, &badge);
        event_handler(data);
    }
}

int run(void)
{
    notification_event_loop();
    return 0;
}
