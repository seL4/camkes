/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>

int run(void) {
    int x = 3;
    int y = 5;
    unsigned int i;
    i = cs_swap(&x, &y);
    /* Printf for tests,
     * you should probably remove this line if wanting to run proofs */
    printf("done\n");
    return 0;
}
