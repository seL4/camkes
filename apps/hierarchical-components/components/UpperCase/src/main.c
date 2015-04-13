/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */


#include <UpperCase.h>
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
