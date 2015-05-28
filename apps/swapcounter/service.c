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

static unsigned int counter;

unsigned int
ss_swap(int *a, int *b){
    int temp = *a;
    *a = *b; *b = temp;
    counter++;
    return counter;
}
