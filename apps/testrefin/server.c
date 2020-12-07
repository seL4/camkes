/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <assert.h>
#include <camkes.h>
#include "my_struct.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int p_echo(const int *x)
{
    assert(x != NULL && "refin parameter not backed by memory");
    printf("%s: %s called with %d\n", get_instance_name(), __func__, *x);
    return *x;
}

void c_echo(const MyStruct *x, MyStruct *y)
{
    assert(x != NULL && "refin parameter not backed by memory");
    assert(y != NULL && "output parameter not backed by memory");
    printf("%s: %s called with {%d..%d}\n", get_instance_name(), __func__,
           x->data[0], x->data[sizeof(x->data) / sizeof(x->data[0]) - 1]);
    memcpy(y, x, sizeof(*x));
}
