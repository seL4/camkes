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

/* Usage of the keyboard in this file is based on information from
 * http://www.win.tue.nl/~aeb/linux/kbd/scancodes-11.html
 */

#include <assert.h>
#include <stdio.h>
#include <camkes.h>
#include <camkes/io.h>

#define KEYBOARD_STATUS_PORT    0x64 /* Control port. */
#define KEYBOARD_DATA_PORT      0x60 /* Input/output port. */

#define KEYBOARD_CCB_WRITE  0x60 /* Write it to the Control port before write a CCB. */
#define KEYBOARD_CCB_READ   0x20 /* Write it to the Control port before read a CCB. */

#define KEYBOARD_ENABLE     0xae /* Keyboard enable command. */
#define KEYBOARD_DISABLE    0xad /* Keyboard disable command. */

static ps_io_port_ops_t io_port_ops;

static uint8_t port_in8(uint16_t port)
{
    uint32_t result = 0;
    int error = ps_io_port_in(&io_port_ops, port, IOSIZE_8, &result);
    if (error) {
        return 0;
    }
    return (uint8_t) result;
}

static uint8_t read_status(void)
{
    char c;
    c = port_in8(KEYBOARD_STATUS_PORT);

    printf("Current Status: 0x%x\n", c);
    return c;
}

static uint8_t read_scancode(void)
{
    return port_in8(KEYBOARD_DATA_PORT);
}

static int keyboard_enable(void)
{
    ps_io_port_out(&io_port_ops, KEYBOARD_STATUS_PORT, IOSIZE_8, KEYBOARD_ENABLE);
    return 0;
}

void interrupt_handle(void)
{
    printf("Scancode: %u\n", read_scancode());
    keypress_emit();
    interrupt_acknowledge();
}

void kbd__init(void)
{
    int error = camkes_io_port_ops(&io_port_ops);
    assert(!error);
    read_status();
    keyboard_enable();
}

int kbd_get_scancode(void)
{
    return read_scancode();
}
