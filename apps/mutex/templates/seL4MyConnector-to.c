/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <assert.h>
#include <sel4/sel4.h>
#include <stddef.h>
#include <sync/mutex.h>
#include <utils/util.h>

/*- set ep = alloc('ep', seL4_EndpointObject, read=True, write=True) -*/
/*- set notification = alloc('notification', seL4_NotificationObject, read=True, write=True) -*/

static sync_mutex_t mutex;

/* We implement the 'to' side of this interface, removing the need for the user
 * to implement it.
 */
int /*? me.interface.name ?*/_lock(void) {
    return sync_mutex_lock(&mutex);
}

int /*? me.interface.name ?*/_unlock(void) {
    return sync_mutex_unlock(&mutex);
}

void /*? me.interface.name ?*/__init(void) {
    int result = sync_mutex_init(&mutex, /*? notification ?*/);
    assert(result == 0);
}

int /*? me.interface.name ?*/__run(void) {
    while (1) {
        /*- if options.realtime -*/
        seL4_MessageInfo_t info = seL4_Wait(/*? ep ?*/, NULL);
        /*- else -*/
        seL4_MessageInfo_t info = seL4_Recv(/*? ep ?*/, NULL);
        /*- endif -*/
        assert(seL4_MessageInfo_get_length(info) == 1);
        if (seL4_GetMR(0) == 0) {
            int result UNUSED = sync_mutex_lock(&mutex);
            assert(result == 0);
        } else {
            int result UNUSED = sync_mutex_unlock(&mutex);
            assert(result == 0);
        }
        info = seL4_MessageInfo_new(0, 0, 0, 0);
        seL4_Send(/*? ep ?*/, info);
    }

    assert(!"unreachable");
    return -1;
}
