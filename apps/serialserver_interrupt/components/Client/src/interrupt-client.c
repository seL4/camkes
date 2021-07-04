/*
 * Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <autoconf.h>
#include <camkes.h>
#include <stdio.h>

#define CLIENT_BUF 20
#define SERIAL_BUF (0x1000 - 8)

struct {
    uint32_t head;
    uint32_t tail;
    char buf[SERIAL_BUF];
} extern volatile *interrupt_getchar_buf;

void pre_init(void)
{
    set_putchar(interrupt_putchar_putchar);
}

int run(void)
{
    printf("%s: Hello Serial Server!\n", get_instance_name());

    char buf[CLIENT_BUF];
    while (1) {
        seL4_Word badge = 0;
        int i = 0;
        do {
            if (interrupt_getchar_buf->head == interrupt_getchar_buf->tail) {
                seL4_Wait(interrupt_getchar_notification(), &badge);
            }
            buf[i] = interrupt_getchar_buf->buf[interrupt_getchar_buf->head];
            interrupt_getchar_buf->head = (interrupt_getchar_buf->head + 1) % sizeof(interrupt_getchar_buf->buf);
        } while (buf[i] != '\r' && ++i < CLIENT_BUF - 1);
        buf[i] = 0;
        printf("%s: %s\n", get_instance_name(), buf);
    }
    return 0;
}
