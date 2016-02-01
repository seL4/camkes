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
#include <stdlib.h>

int run(void) {
    printf("Looking up key \"foo\"...");
    char *value = l_get_value("foo");
    printf("received value \"%s\"\n", value);
    free(value);

    printf("\nNow try to read something I shouldn't be able to...\n");
    printf("Looking up key \"secret\"...");
    value = l_get_value("secret");
    printf("received value \"%s\"\n", value);
    free(value);
    return 0;
}
