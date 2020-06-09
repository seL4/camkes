/*
 * Copyright 2018, 2020, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#include <autoconf.h>
#include <camkes.h>
#include <stdio.h>

#define CLIENT_BUF 20
#define GETCHAR_BUF (0x1000 - 8)

struct {
    uint32_t head;
    uint32_t tail;
    char buf[GETCHAR_BUF];
} extern volatile *poll_getchar_buf;

void pre_init(void)
{
    set_putchar(poll_putchar_putchar);
}

int run(void)
{
    printf("%s: Hello Serial Server!\n", get_instance_name());

    char buf[CLIENT_BUF];
    while (1) {
        int i = 0;
        do {
            seL4_Word badge = 0;
            while (!badge) {
                seL4_Poll(poll_getchar_notification(), &badge);
            }
            buf[i] = poll_getchar_buf->buf[poll_getchar_buf->head];
            poll_getchar_buf->head = (poll_getchar_buf->head + 1) % sizeof(poll_getchar_buf->buf);
        } while (buf[i] != '\r' && ++i < CLIENT_BUF - 1);
        buf[i] = 0;
        printf("%s: %s\n", get_instance_name(), buf);
    }

    return 0;
}
