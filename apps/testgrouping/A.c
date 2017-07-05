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

#include <assert.h>
#include <camkes.h>

int run(void) {
    int x = 0;

    int y = p_increment(x);

#ifdef NDEBUG
    printf("WARNING: ASSERTIONS DISABLED; NOTHING WILL BE TESTED\n");
#endif
    assert(y == 8);

    printf("All OK\n");

    return 0;
}
