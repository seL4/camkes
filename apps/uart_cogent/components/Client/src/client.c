/*
 * Copyright 2019, Data61
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
