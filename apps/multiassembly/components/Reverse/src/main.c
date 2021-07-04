/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdlib.h>
#include <string.h>

void i_process(const char *arg)
{
    char *str = strdup(arg);
    int last_idx = strlen(str) - 1;
    for (int i = 0; i < last_idx / 2; i++) {
        char tmp = str[i];
        str[i] = str[last_idx - i];
        str[last_idx - i] = tmp;
    }

    o_process(str);
    free(str);
}
