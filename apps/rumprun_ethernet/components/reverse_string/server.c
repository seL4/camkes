/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <buffer.h>
#include <string.h>
#include <stdio.h>

int run(void)
{

    char *buffer_str = (char *)buffer;
    while (true) {
        /* Wait for event */
        ev_wait();
        printf("Got string: %s\n", buffer_str);

        int len = strnlen(buffer_str, REVERSE_STRING_MAX_LEN);
        for (int i = 0; i < len / 2; ++i) {
            int swap_idx = len - i - 1;
            char tmp = buffer_str[i];
            buffer_str[i] = buffer_str[swap_idx];
            buffer_str[swap_idx] = tmp;
        }

        /* Signal to client that we are finished */
        ev1_emit();
    }

    return 0;
}
