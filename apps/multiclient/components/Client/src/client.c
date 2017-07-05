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
