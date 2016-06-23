/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

/* Force assertions on. */
#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <assert.h>
#include <camkes.h>
#include <sys/types.h>
#include <unistd.h>

static void test_getpid(void) {
    /* Check that our PID is what we expect. */
    pid_t pid = getpid();
    assert(pid == 3);
}

void other_call(void) {
    test_getpid();
}
