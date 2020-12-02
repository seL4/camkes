/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>

void event_reg_callback(void *_ UNUSED)
{
    printf("client Event received!\n");
    e_reg_callback(&event_reg_callback, NULL);
}

int run() {
    int j;

    printf("Starting the client\n");
    printf("-------------------\n");

    e_reg_callback(&event_reg_callback, NULL);

    j = s_echo_int();
    printf("echo_int: %d\n", j);

    printf("%s\n", (char*)d);

    printf("After the client\n");
    return 0;
}
