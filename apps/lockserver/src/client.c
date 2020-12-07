/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>

int run(void)
{
    printf("%s: starting...\n", get_instance_name());
    l_lock();
    printf("%s: got lock!\n", get_instance_name());
    l_unlock();
    printf("%s: released\n", get_instance_name());
    return 0;
}
