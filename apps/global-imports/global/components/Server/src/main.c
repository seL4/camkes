/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <string.h>
#include <vec.h>

void getter__init(void)
{
    counter->value = 0;
}

char *getter_get_string(void)
{
    counter->value++;
    return strdup("Hello, World!\n");
}

vec_t getter_get_vec(void)
{
    counter->value++;
    return (vec_t) {
        .x = 4.0, .y = 2.0
    };
}
