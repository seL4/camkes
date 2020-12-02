/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <autoconf.h>
#include <camkes.h>
#include <camkes/io.h>
#include <stdio.h>
#include <platsupport/plat/pit.h>
#include <utils/time.h>

#define IRQS_PER_SECOND 100

static pit_t timer;

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
    ps_io_port_ops_t ops = {0};
    error = camkes_io_port_ops(&ops);
    assert(!error);
    error = pit_init(&timer, ops);
    assert(!error);
    error = pit_set_timeout(&timer, NS_IN_S / IRQS_PER_SECOND, true);
    assert(!error);
    irq_acknowledge();
}
