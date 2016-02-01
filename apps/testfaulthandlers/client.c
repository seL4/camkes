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
