/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>

static unsigned int counter;

unsigned int ss_swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    counter++;
    return counter;
}
