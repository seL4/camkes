/*
 * Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <sel4/sel4.h>

int run(void)
{

    while (1) {
        ev_emit();
    }

    return 0;
}

