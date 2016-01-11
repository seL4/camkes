/*
 * Copyright 2015, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <camkes.h>
#include <stddef.h>
#include <stdint.h>

extern char *morecore_area;
extern size_t morecore_size;

int run(void) {
    m_morecore_range((uintptr_t)morecore_area, morecore_size);
    return 0;
}
