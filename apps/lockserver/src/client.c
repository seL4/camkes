/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <stdio.h>
#include <Client.h>

int run(void) {
    printf("%s: starting...\n", get_instance_name());
    l_lock();
    printf("%s: got lock!\n", get_instance_name());
    l_unlock();
    printf("%s: released\n", get_instance_name());
    return 0;
}
