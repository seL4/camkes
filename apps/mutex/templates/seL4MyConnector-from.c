/* @TAG(DATA61_BSD) */

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
