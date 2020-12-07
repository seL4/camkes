/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <assert.h>
#include <camkes.h>

int run(void)
{
    int x = 0;

    int y = p_increment(x);

#ifdef NDEBUG
    printf("WARNING: ASSERTIONS DISABLED; NOTHING WILL BE TESTED\n");
#endif
    assert(y == 8);

    printf("All OK\n");

    return 0;
}
