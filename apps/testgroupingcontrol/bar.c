/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>

static unsigned ping_count;

void p_ping(void)
{
    ping_count++;
    if (ping_count == 2) {
        printf("All OK\n");
    } else if (ping_count > 2) {
        printf("FAIL\n");
    }
}
