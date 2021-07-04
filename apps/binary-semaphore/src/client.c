/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <stdio.h>
#include <camkes.h>

#define TO_ECHO 42

int run(void)
{

    printf("Echoing: %d == %d\n", TO_ECHO, echo_echo(TO_ECHO));

    return 0;
}
