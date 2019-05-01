/*
 * Copyright 2018, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#include <autoconf.h>
#include <camkes.h>
#include <stdio.h>

#define TICKS 3 /* amount of ticks to periodically wait for */
#define WAIT (10 * NS_IN_MS) /* amount of time to set timeouts for */

seL4_CPtr timeout_notification(void);

int run(void)
{
    seL4_Word badge;
    seL4_CPtr notification = timeout_notification();

    /* test we can read the time */
    uint64_t t1 = timeout_time();

    /* test a periodic timeout */
    timeout_periodic(0, WAIT);
    for (int i = 0; i < TICKS; i++) {
        seL4_Wait(notification, &badge);
        printf("Tick\n");
    }
    uint64_t t2 = timeout_time();
    assert(t2 - t1 >= TICKS * WAIT);

    /* test a relative timeout */
    timeout_oneshot_relative(0, WAIT);
    seL4_Wait(notification, &badge);
    printf("Tick\n");

    /* test an absolute timeout */
    t1 = timeout_time();
    timeout_oneshot_absolute(0, t1 + WAIT);
    seL4_Wait(notification, &badge);
    printf("Tick\n");
    t2 = timeout_time();
    assert(t2 - t1 >= WAIT);

    timeout_stop(0);
    printf("BOOM!\n");

    return 0;
}
