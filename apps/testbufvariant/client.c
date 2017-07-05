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

#include <camkes.h>
#include <stdint.h>
#include <utils/util.h>

int run(void) {
    /* Test we can write something at an offset into our dataport that is
     * actually beyond what we declared, but should still be in the same pages.
     */
    printf("%s: Writing a number...\n", get_instance_name());
    *(volatile int*)((uintptr_t)d + PAGE_SIZE_4K + PAGE_SIZE_4K - 512) = 42;

    printf("%s: Switching to partner...\n", get_instance_name());
    s_switch_to();

    printf("All OK\n");

    return 0;
}
