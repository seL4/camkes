/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>

int run(void) {
    printf("%s: Calling Receiver...\n", get_instance_name());
    a_switch_to();

    printf("All OK\n");

    return 0;
}
