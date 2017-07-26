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

#include <autoconf.h>
#include <camkes.h>
#include <stdio.h>
#include <platsupport/plat/pit.h>
#include <utils/time.h>

#define IRQS_PER_SECOND 100

static pit_t timer;

static int pit_port_in(void *cookie, uint32_t port, int io_size, uint32_t *result) {
    if (io_size != 1) {
        return -1;
    }
    switch(port) {
    case 0x43:
        *result = command_in8(port);
        return 0;
    case 0x40:
        *result = channel0_in8(port);
        return 0;
    default:
        return -1;
    }
}

static int pit_port_out(void *cookie, uint32_t port, int io_size, uint32_t val) {
    if (io_size != 1) {
        return -1;
    }
    switch(port) {
    case 0x43:
        command_out8(port, val);
        return 0;
    case 0x40:
        channel0_out8(port, val);
        return 0;
    default:
        return -1;
    }
}

void irq_handle(void)
{
    static int count = 0;
    static int seconds = 0;
    if (++count == IRQS_PER_SECOND) {
        seconds++;
        printf("%d seconds elapsed\n", seconds);
        count = 0;
    }
    irq_acknowledge();
}

void pre_init(void)
{
    int error;
    ps_io_port_ops_t ops = (ps_io_port_ops_t){.io_port_in_fn = pit_port_in, .io_port_out_fn = pit_port_out};
    error = pit_init(&timer, ops);
    assert(!error);
    error = pit_set_timeout(&timer, NS_IN_S / IRQS_PER_SECOND, true);
    assert(!error);
    irq_acknowledge();
}
