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
#include <stdio.h>
#include <utils/util.h>

static void stack_overflow(void) {
    char x[1024] UNUSED;
    asm volatile("");
    stack_overflow();
    asm volatile("");
}

int run() {
    printf("%s: Attempting to cause a stack overflow...\n",
        get_instance_name());
    stack_overflow();
    return 0;
}
