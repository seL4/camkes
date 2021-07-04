/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <assert.h>
#include <camkes.h>
#include <stdio.h>

int run(void)
{
#ifdef NDEBUG
    printf("WARNING: assertions are disabled!\n");
#endif

    /* Write something to the first dataport. */
    printf("Writing 42...\n");
    *(volatile int *)d1 = 42;

    /* Make sure we can read it back from the second. */
    int x = *(volatile int *)d2;
    assert(x == 42);

    /* Chain this through all the others. */

    *(volatile int *)d2 = 43;
    x = *(volatile int *)d3;
    assert(x == 43);

    *(volatile int *)d3 = 44;
    x = *(volatile int *)d4;
    assert(x == 44);

    *(volatile int *)d4 = 45;
    x = *(volatile int *)d1;
    assert(x == 45);

    printf("All OK\n");
    return 0;
}
