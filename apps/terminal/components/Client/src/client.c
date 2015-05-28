/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <camkes.h>
#include <stdio.h>

/* Print a string starting at (0,0) in our region. */
static void print(const char *msg) {
    int i = 0;
    while (*msg != '\0') {
        if (d_put_char(i++, 0, *msg++) != 0) {
            /* Failed. Potentially the string was too wide for our region. */
            return;
        }
    }
}

int run(void) {
    /* XXX: This is a hack to make sure client 1 executes after client 2. If
     * they execute in parallel there is a race condition and, with no lock on
     * d_put_char, the escape characters corrupt the terminal.
     */
    if (ID == 1) {
        for (int i = 0; i < 10000; ++i) {
            asm volatile ("");
        }
    }

    /* MESSAGE comes as an attribute. */
    print(MESSAGE);
    return 0;
}
