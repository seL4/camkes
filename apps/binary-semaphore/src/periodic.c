/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <camkes.h>

int run(void)
{

    while (1) {
        ready_emit();
    }

    return 0;
}
