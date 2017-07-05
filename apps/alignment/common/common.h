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

/* A couple of operations that should trigger faults on x86 if
 * our stack isn't set up correctly.
 */

#pragma once

#include <string.h>

typedef struct foo {
    float arr[4];
} foo_t;

/* Hopefully the compiler will attempt to optimize this
 * function with sse instructions on x86.
 */
static inline void memcpy_test(foo_t *a, foo_t *b) {
    foo_t intermediate = *a;
    intermediate.arr[1] += 0.5;
    memcpy(b, &intermediate, sizeof(foo_t));
}

/* Implemented in assembly */
void movaps_test(void);

/* Hopefully this function will result in a GP fault due
 * to unaligned operands of sse instructions with alignment
 * requirements, unless the stack is correctly aligned.
 */
static inline void test_alignment(void) {
    foo_t a, b;
    a.arr[0] = 0.1;
    a.arr[1] = 0.2;
    a.arr[2] = 0.3;
    a.arr[3] = 0.4;

    memcpy_test(&a, &b);
    movaps_test();

    printf("Done testing alignment: %f\n", b.arr[1]);
}
