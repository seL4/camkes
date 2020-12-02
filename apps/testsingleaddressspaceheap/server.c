/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
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
