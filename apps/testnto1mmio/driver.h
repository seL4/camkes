/* @TAG(NICTA_BSD) */

#ifndef DRIVER_H_
#define DRIVER_H_

#include <camkes.h>
#include <stdint.h>

#define KZM_IO_BASE_ADDR    (unsigned int)regs
#define KZM_UART1_RX_ADDR   (KZM_IO_BASE_ADDR + 0x00) 
#define KZM_UART1_TX_ADDR   (KZM_IO_BASE_ADDR + 0x40) 
#define KZM_UART1_STAT_ADDR (KZM_IO_BASE_ADDR + 0x94) 

#define KZM_UART1_RX_RDY (1UL << 9)
#define KZM_UART1_TX_RDY (1UL << 13)
#define KZM_UART1_RX_MASK 0xFF

#define UART_VAL(x) *((volatile uint32_t *)(x))

static inline int uart_received()
{
	return UART_VAL(KZM_UART1_STAT_ADDR) & KZM_UART1_RX_RDY;
}

static inline int is_transmit_empty() {
	   return UART_VAL(KZM_UART1_STAT_ADDR) & KZM_UART1_TX_RDY;
}

static inline void uart_put_char(char c)
{
	while(is_transmit_empty() == 0);
	UART_VAL(KZM_UART1_TX_ADDR) = c;
}

static inline void uart_put(const char *s) {
    while (*s != '\0') {
        uart_put_char(*s);
        s++;
    }
}

#endif
