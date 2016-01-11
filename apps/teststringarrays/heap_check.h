/*
 * Copyright 2015, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#ifndef HEAP_CHECK_H_
#define HEAP_CHECK_H_

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

static inline bool is_heap_pointer(void *p) {
    extern char *morecore_area;
    extern size_t morecore_size;
    return (uintptr_t)morecore_area <= (uintptr_t)p &&
           (uintptr_t)morecore_area + morecore_size > (uintptr_t)p;
}

static inline void safe_free(void *p) {
    assert(is_heap_pointer(p));
    free(p);
}

#endif
