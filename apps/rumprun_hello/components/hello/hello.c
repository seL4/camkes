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

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    printf("Hello %s\n", argv[1]);
    printf("sleep 1 sec\n");
    sleep(1);
    printf("sleep 10 sec\n");
    sleep(10);
    printf("finished sleep\n");
}
