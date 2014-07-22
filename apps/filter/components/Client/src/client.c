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
    printf("Looking up key \"foo\"...");
    char *value = l_get_value("foo");
    printf("received value \"%s\"\n", value);

    printf("\nNow try to read something I shouldn't be able to...\n");
    printf("Looking up key \"secret\"...");
    value = l_get_value("secret");
    printf("received value \"%s\"\n", value);
    return 0;
}
