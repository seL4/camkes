/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#include <camkes.h>
#include <stdio.h>

int run(void) {
    printf("%s: starting...\n", get_instance_name());
    l_lock();
    printf("%s: got lock!\n", get_instance_name());
    l_unlock();
    printf("%s: released\n", get_instance_name());
    return 0;
}
