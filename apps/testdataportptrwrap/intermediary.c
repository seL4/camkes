/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <assert.h>
#include <camkes.h>
#include <stddef.h>
#include <stdint.h>

void p1_post(dataport_ptr_t ptr)
{
    assert(ptr.id != -1);
    volatile int *x = dataport_unwrap_ptr(ptr);
    assert(x != NULL);
    assert(*x == 42);
    volatile int *y = (volatile int *)((uintptr_t)d + 32);
    *y = *x;
    dataport_ptr_t ptr2 = dataport_wrap_ptr((void *)y);
    assert(ptr2.id != -1);
    p2_post(ptr2);
}
