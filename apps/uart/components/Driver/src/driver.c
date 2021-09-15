/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <autoconf.h>
#include <camkes.h>
#include <stdint.h>
#include <stdio.h>

#define IO_BASE_ADDR    (unsigned int)mem
#define UART1_RX_ADDR   (IO_BASE_ADDR + 0x00)
#define UART1_TX_ADDR   (IO_BASE_ADDR + 0x40)
#define UART1_STAT_ADDR (IO_BASE_ADDR + 0x94)

#define UART1_RX_RDY (1UL << 9)
#define UART1_TX_RDY (1UL << 13)
#define UART1_RX_MASK 0xFF

#define UART_VAL(x) *((volatile uint32_t *)(x))

void uart__init()
{
    printf("uart port init\n");
}

static int uart_received()
{
    return UART_VAL(UART1_STAT_ADDR) & UART1_RX_RDY;
}

static int is_transmit_empty()
{
    return UART_VAL(UART1_STAT_ADDR) & UART1_TX_RDY;
}

char uart_get_char()
{
    while (uart_received() == 0);
    return UART_VAL(UART1_RX_ADDR) & UART1_RX_MASK;
}

void uart_put_char(char c)
{
    while (is_transmit_empty() == 0);
    UART_VAL(UART1_TX_ADDR) = c;
}
