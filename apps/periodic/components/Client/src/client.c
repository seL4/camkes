/*
 * Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

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
            IPRINT("acc = %"PRIuPTR"\n", acc);
            seL4_Yield();
        }
    }

    IPRINT("*** DONE %"PRIuPTR" ***\n", acc);

    return 0;
}
