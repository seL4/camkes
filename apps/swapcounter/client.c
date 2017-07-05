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
