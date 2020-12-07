/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <string.h>
#include <sel4/sel4.h>

int run(void)
{
    const char *shello = "hello world";

    printf("Starting...\n");
    printf("-----------\n");

    strcpy((void *)DataOut, shello);
    while (!*((char *)DataIn)) {
        seL4_Yield();
    }
    printf("%s read %s\n", get_instance_name(), (char *)DataIn);
    return 0;
}
