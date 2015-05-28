/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <camkes.h>
#include <stdio.h>

void event_reg_callback(void *_ UNUSED)
{
    printf("Sender Event received!\n");
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
