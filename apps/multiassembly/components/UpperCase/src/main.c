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
#include <stdlib.h>
#include <string.h>

#define TO_UPPER_DIST ('A' - 'a')

void i_process(const char *arg) {
    char *str = strdup(arg);
    for (char *cptr = str;*cptr != '\0';cptr++) {
        if (*cptr >= 'a' && *cptr <= 'z') {
            *cptr += TO_UPPER_DIST;
        }
    }

    o_process(str);
    free(str);
}
