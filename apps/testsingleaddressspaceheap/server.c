/*
 * Copyright 2015, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <assert.h>
#include <camkes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

extern char *morecore_area;
extern size_t morecore_size;

void m_morecore_range(uintptr_t base, size_t size) {
    printf("Server's range is %p - %p\n"
           "Client's range is %p - %p\n", (void*)morecore_area,
           (void*)((uintptr_t)morecore_area + morecore_size), (void*)base,
           (void*)(base + size));
#ifdef NDEBUG
    printf("WARNING: ASSERTIONS DISABLED; NOTHING WILL BE TESTED\n");
#endif
    assert(((uintptr_t)morecore_area + morecore_size <= base ||
            base + size <= (uintptr_t)morecore_area) &&
        "morecore regions overlap");
    printf("All OK\n");
}
