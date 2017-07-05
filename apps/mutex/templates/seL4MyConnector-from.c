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

#include <stdlib.h>
#include <sel4/sel4.h>
#include <stddef.h>

/*- set ep = alloc('ep', seL4_EndpointObject, read=True, write=True) -*/

int /*? me.interface.name ?*/__run(void) {
    /* No setup required */
    return 0;
}

int /*? me.interface.name ?*/_lock(void) {
    seL4_SetMR(0, 0);
    seL4_MessageInfo_t info = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_Send(/*? ep ?*/, info);
    seL4_Wait(/*? ep ?*/, NULL);
    return 0;
}

int /*? me.interface.name ?*/_unlock(void) {
    seL4_SetMR(0, 1);
    seL4_MessageInfo_t info = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_Send(/*? ep ?*/, info);
    seL4_Wait(/*? ep ?*/, NULL);
    return 0;
}
