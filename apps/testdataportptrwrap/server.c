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
#include <stddef.h>
#include <stdint.h>

void p_post(dataport_ptr_t ptr) {
    assert(ptr.id != -1);
    volatile int *x = dataport_unwrap_ptr(ptr);
    assert(x != NULL);
    assert(*x == 42);
}
