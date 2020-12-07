/*
 * Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>

void client_transfer_string(const char *s)
{
    printf("%s", s);
    fflush(stdout);
}
