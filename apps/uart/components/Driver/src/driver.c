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
#include <stdint.h>
#include <stdio.h>

#define KZM_IO_BASE_ADDR    (unsigned int)mem
#define KZM_UART1_RX_ADDR   (KZM_IO_BASE_ADDR + 0x00) 
#define KZM_UART1_TX_ADDR   (KZM_IO_BASE_ADDR + 0x40) 
#define KZM_UART1_STAT_ADDR (KZM_IO_BASE_ADDR + 0x94) 

#define KZM_UART1_RX_RDY (1UL << 9)
#define KZM_UART1_TX_RDY (1UL << 13)
#define KZM_UART1_RX_MASK 0xFF

#define UART_VAL(x) *((volatile uint32_t *)(x))

void uart__init()
{
	printf("uart port init\n");
}

static int uart_received()
{
	return UART_VAL(KZM_UART1_STAT_ADDR) & KZM_UART1_RX_RDY;
}

static int is_transmit_empty() {
	   return UART_VAL(KZM_UART1_STAT_ADDR) & KZM_UART1_TX_RDY;
}

char uart_get_char()
{
	while (uart_received() == 0);
	return UART_VAL(KZM_UART1_RX_ADDR) & KZM_UART1_RX_MASK;
}

void uart_put_char(char c)
{
	while(is_transmit_empty() == 0);
	UART_VAL(KZM_UART1_TX_ADDR) = c;
}
