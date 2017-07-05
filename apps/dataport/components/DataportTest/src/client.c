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
#include <string.h>
#include <sel4/sel4.h>

int run(void) {
    const char *shello = "hello world";

    printf("Starting...\n");
    printf("-----------\n");

    strcpy((void*)DataOut, shello);
    while(!*((char*)DataIn))
        seL4_Yield();
    printf("%s read %s\n", get_instance_name(), (char*)DataIn);
    return 0;
}
