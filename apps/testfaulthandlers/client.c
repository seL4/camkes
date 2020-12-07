/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <utils/util.h>

static void stack_overflow(void)
{
    char x[1024] UNUSED;
    asm volatile("");
    stack_overflow();
    asm volatile("");
}

int run()
{
    printf("%s: Attempting to cause a stack overflow...\n",
           get_instance_name());
    stack_overflow();
    return 0;
}
