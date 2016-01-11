/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <autoconf.h>
#include <assert.h>
#include <camkes.h>
#include <stdio.h>

#ifdef NDEBUG
    #error "this test application needs assertions enabled"
#endif

#ifdef CONFIG_CAMKES_OPTIMISATION_CALL_LEAVE_REPLY_CAP
    #error "this test required lazy save of reply caps to be disabled"
#endif

int incoming_echo(int x) {
    return x;
}

int run(void) {
    int y = outgoing_echo(42);
    assert(y == 42);
    printf("All OK\n");
    return 0;
}
