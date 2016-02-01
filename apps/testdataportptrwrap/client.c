/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <assert.h>
#include <camkes.h>
#include <stdint.h>
#include <stdio.h>

int run(void) {
#ifdef NDEBUG
    printf("WARNING: assertions are disabled!\n");
#endif

    volatile int *x = (volatile int*)((uintptr_t)d + 16);
    *x = 42;
    dataport_ptr_t ptr = dataport_wrap_ptr((void*)x);
    assert(ptr.id != -1);
    p_post(ptr);

    printf("All OK\n");

    return 0;
}
