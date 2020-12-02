/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>

#include "common.h"

void b_f(void) {
    printf("Server is testing alignment...\n");
    test_alignment();
}
