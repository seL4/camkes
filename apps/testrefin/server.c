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
#include "my_struct.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int p_echo(const int *x) {
    assert(x != NULL && "refin parameter not backed by memory");
    printf("%s: %s called with %d\n", get_instance_name(), __func__, *x);
    return *x;
}

void c_echo(const MyStruct *x, MyStruct *y) {
    assert(x != NULL && "refin parameter not backed by memory");
    assert(y != NULL && "output parameter not backed by memory");
    printf("%s: %s called with {%d..%d}\n", get_instance_name(), __func__,
        x->data[0], x->data[sizeof(x->data) / sizeof(x->data[0]) - 1]);
    memcpy(y, x, sizeof(*x));
}
