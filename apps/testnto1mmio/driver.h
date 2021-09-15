/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <camkes.h>
#include <stdint.h>

#define IO_BASE_ADDR    (unsigned int)regs
#define UART1_RX_ADDR   (IO_BASE_ADDR + 0x00)
#define UART1_TX_ADDR   (IO_BASE_ADDR + 0x40)
#define UART1_STAT_ADDR (IO_BASE_ADDR + 0x94)

#define UART1_RX_RDY (1UL << 9)
#define UART1_TX_RDY (1UL << 13)
#define UART1_RX_MASK 0xFF

#define UART_VAL(x) *((volatile uint32_t *)(x))

static inline int uart_received()
{
    return UART_VAL(UART1_STAT_ADDR) & UART1_RX_RDY;
}

static inline int is_transmit_empty()
{
    return UART_VAL(UART1_STAT_ADDR) & UART1_TX_RDY;
}

static inline void uart_put_char(char c)
{
    while (is_transmit_empty() == 0);
    UART_VAL(UART1_TX_ADDR) = c;
}

static inline void uart_put(const char *s)
{
    while (*s != '\0') {
        uart_put_char(*s);
        s++;
    }
}
