/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdint.h>
#include <utils/util.h>

void s_switch_to(void) {
    /* Test that we can read what the client wrote. */
    while (*(volatile int*)((uintptr_t)d + PAGE_SIZE_4K + PAGE_SIZE_4K - 512) != 42);
}
