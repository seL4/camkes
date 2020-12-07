/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 128

void i_process(const char *str)
{
    char buf[BUF_SIZE];
    snprintf(buf, BUF_SIZE, "%s%s", str, string_to_append);

    o_process(buf);
}
