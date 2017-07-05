/*
 * Copyright 2016, Data61
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
#include <buffer.h>
#include <string.h>
#include <stdio.h>

int run(void) {

    char *buffer_str = (char*)buffer;

    snprintf(buffer_str, REVERSE_STRING_MAX_LEN, "Hello, World!");

    printf("Sending string: %s\n", buffer_str);

    /* The following write to the buffer signals to the server
     * that the client is ready for the string to be reversed.
     * This release is necessary to prevent the following write
     * being re-ordered with the preceeding writes (by snprintf),
     * which map happen as they are non-overlapping. */
    buffer_release();

    buffer_str[REVERSE_STRING_END_IDX] = 1;

    while (buffer_str[REVERSE_STRING_END_IDX] != 0) {
        /* Poll the last byte of the buffer until the server has
         * reversed the string. This acquire is necessary to
         * prevent the compiler from coalescing the reads and
         * looping forever. */
        buffer_acquire();
    }

    printf("%s\n", buffer_str);

    return 0;
}
