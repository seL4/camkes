/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>

MyType_t s_rotate(MyType_t a, MyType_t *b, MyType_t *c) {
    b->i = c->i;
    c->i = a.i;
    return a;
}
