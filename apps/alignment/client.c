/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>

#include "common.h"

int run() {
    printf("Calling server...\n");
    a_f();
    printf("Back from server!\n");
    printf("Client is testing alignment...\n");
    test_alignment();
    printf("All is well in the universe!\n");

    return 0;
}
