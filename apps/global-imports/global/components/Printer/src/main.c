/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <vec.h>

void printer_print_string(const char *str)
{
    printf("%s", str);
}
void printer_print_vec(vec_t v)
{
    printf("(%2f, %2f)\n", v.x, v.y);
}
