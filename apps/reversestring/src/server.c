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

    while (buffer_str[REVERSE_STRING_END_IDX] == 0) {
        /* Poll the last byte of the buffer until the client is
         * ready. This acquire is necessary to prevent the compiler
         * from coalescing the reads and looping forever. */
        buffer_acquire();
    }

    printf("Got string: %s\n", buffer_str);

    int len = strnlen(buffer_str, REVERSE_STRING_MAX_LEN);
    for (int i = 0; i < len / 2; ++i) {
        int swap_idx = len - i - 1;
        char tmp = buffer_str[i];
        buffer_str[i] = buffer_str[swap_idx];
        buffer_str[swap_idx] = tmp;
    }

    /* The following write to the buffer signals to the client
     * that the server has finished reversing the string. This
     * release is necessary to prevent the following write
     * being re-ordered with the preceeding writes, which may
     * otherwise happen as they are non-overlapping. */
    buffer_release();

    buffer_str[REVERSE_STRING_END_IDX] = 0;

    return 0;
}
