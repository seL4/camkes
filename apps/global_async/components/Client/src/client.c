/*
 * Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
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
