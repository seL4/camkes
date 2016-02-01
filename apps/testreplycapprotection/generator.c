/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <camkes.h>
#include <stdio.h>

int run(void) {
    printf("%s: Calling Receiver...\n", get_instance_name());
    a_switch_to();

    printf("All OK\n");

    return 0;
}
