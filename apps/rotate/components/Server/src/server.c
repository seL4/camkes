/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <camkes.h>

MyType_t s_rotate(MyType_t a, MyType_t *b, MyType_t *c) {
    b->i = c->i;
    c->i = a.i;
    return a;
}
