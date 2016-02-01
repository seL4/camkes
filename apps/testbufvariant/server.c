/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <camkes.h>
#include <stdint.h>
#include <utils/util.h>

void s_switch_to(void) {
    /* Test that we can read what the client wrote. */
    while (*(volatile int*)((uintptr_t)d + PAGE_SIZE_4K + PAGE_SIZE_4K - 512) != 42);
}
