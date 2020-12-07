/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <vec.h>
#include <shared_int.h>

int run(void)
{
    char *str = g_get_string();
    p_print_string(str);
    vec_t vec = g_get_vec();
    p_print_vec(vec);

    printf("%d\n", counter->value);

    return 0;
}
