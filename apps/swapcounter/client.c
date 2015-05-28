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

int run(void) {
    int x = 3;
    int y = 5;
    unsigned int i;
    i = cs_swap(&x, &y);
    return 0;
}
