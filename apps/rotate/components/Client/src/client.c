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
#include <stdio.h>

int run(void) {
    MyType_t a, b, c, d;

    a.i = 1;
    b.i = 2;
    c.i = 3;
    d.i = 4;

    printf("Beforehand we have (ret)%d, (in)%d, (out)%d, (inout)%d\n", a.i, b.i, c.i, d.i);
    a = p_rotate(b, &c, &d);
    printf("Afterwards we have (ret)%d, (in)%d, (out)%d, (inout)%d\n", a.i, b.i, c.i, d.i);
    return 0;
}
