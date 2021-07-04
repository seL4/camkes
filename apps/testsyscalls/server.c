/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

/* Force assertions on. */
#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <assert.h>
#include <camkes.h>
#include <sys/types.h>
#include <unistd.h>

static void test_getpid(void)
{
    /* Check that our PID is what we expect. */
    pid_t pid = getpid();
    assert(pid == 3);
}

static void test_getppid(void)
{
    /* Check that our parent is the CapDL initialiser. */
    pid_t pid = getppid();
    assert(pid == 1);
}

void other_call(void)
{
    test_getpid();

    test_getppid();
}
