/*
 * Copyright 2015, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <assert.h>
#include <camkes.h>
#include <stddef.h>
#include <stdint.h>

void p1_post(dataport_ptr_t ptr) {
    assert(ptr.id != -1);
    volatile int *x = dataport_unwrap_ptr(ptr);
    assert(x != NULL);
    assert(*x == 42);
    volatile int *y = (volatile int*)((uintptr_t)d + 32);
    *y = *x;
    dataport_ptr_t ptr2 = dataport_wrap_ptr((void*)y);
    assert(ptr2.id != -1);
    p2_post(ptr2);
}
