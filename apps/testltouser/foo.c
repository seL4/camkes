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
#include <stdio.h>

#ifdef NDEBUG
    #error "this test application needs assertions enabled"
#endif

/* Implemented in bar.c */
extern void *callee(void);

/* If LTO is working correctly, this function will be flattened. */
void caller(void) {
    void *f = callee();
    assert(f == __builtin_frame_address(0) &&
        "cross-file inlining not applied");
}

int run(void) {
    caller();
    printf("All OK\n");
    return 0;
}
