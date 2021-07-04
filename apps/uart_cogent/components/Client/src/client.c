/*
 * Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
static size_t uart_write(void *buf, size_t count)
{
    char *data = buf;

    for (size_t i = 0; i < count; ++i) {
        uart_put_char(data[i]);
    }

    return count;
}

int run(void)
{
    signed char c;
    char *str = "This message is sent via UART.\n";


    uart_write(str, strlen(str));

    while (1) {
        c = uart_get_char();
        if (c != -1) {
            printf("Input from UART: %c\n", c);
        }

        if (c == 'q') {
            break;
        }

    }

    printf("UART client exit...\n");
    return 0;
}
