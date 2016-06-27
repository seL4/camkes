/*
 * Copyright 2015, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <camkes.h>
#include <stdio.h>
#include <stdlib.h>

#define IPRINT(format, ...) printf("%s: " format, get_instance_name(), ##__VA_ARGS__); 

#define MAX_VALUE  100000llu
#define RATE  10000llu

uint64_t acc = 0;

int run() {

    IPRINT("--- Starting ---\n");

    while (acc < MAX_VALUE) {
        /* do calculations to waste time */
        acc *= 17;
        acc++;
        acc /= 17;
        acc++;
        if (acc % RATE == 0) {
            IPRINT("acc = %llu\n", acc);
        }
    }

    IPRINT("*** DONE %llu ***\n", acc);

    return 0;
}
