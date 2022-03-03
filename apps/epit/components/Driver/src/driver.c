/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <autoconf.h>
#include <camkes.h>
#include <stdio.h>

#define EPIT_BASE_ADDR  (unsigned int)mem
#define EPIT_CTRL_ADDR  (EPIT_BASE_ADDR + 0x00)
#define EPIT_STAT_ADDR  (EPIT_BASE_ADDR + 0x04)
#define EPIT_LOAD_ADDR  (EPIT_BASE_ADDR + 0x08)
#define EPIT_COMP_ADDR  (EPIT_BASE_ADDR + 0x0C)
#define EPIT_CNT_ADDR   (EPIT_BASE_ADDR + 0x10)

#define REG_VAL(x)         *((volatile uint32_t *)(x))

#define CTRL_EN       (1 << 0)   /* EPIT enable */
#define CTRL_ENMOD    (1 << 1)   /* EPIT enable mode */
#define CTRL_OCIEN    (1 << 2)   /* EPIT interrupt enable */
#define CTRL_RLD      (1 << 3)   /* Counter reload control */
#define CTRL_SWR      (1 << 17)  /* Software reset */

#define CTRL_CLKSRC_SHIFT   (24)    /* Clock source */
#define CTRL_PRESCALE_SHIFT (4)     /* Prescalar */

//#define IPG_CLK_KHZ       (53200)     /* Clock frequency in KHz */
#define IPG_CLK_KHZ       (66000)     /* Clock frequency in KHz */
#define CLKSRC_IPG        (0x1)     /* IPG clock */
#define CLKSRC_IPG_HIGH   (0x2)     /* IPG clock high frequency */
#define CLKSRC_IPG_32K    (0x3)     /* IPG 32K clock */

void epit_init()
{
    printf("EPIT init\n");

    REG_VAL(EPIT_CTRL_ADDR) = 0;

    /* Disable EPIT and reset. */
    REG_VAL(EPIT_CTRL_ADDR) = CTRL_SWR;

    /* Select Clock source */
    REG_VAL(EPIT_CTRL_ADDR) = (CLKSRC_IPG << CTRL_CLKSRC_SHIFT);

    /* Reload from load register */
    REG_VAL(EPIT_CTRL_ADDR) |= (CTRL_RLD | CTRL_ENMOD);

    /* Enable interrupt */
    REG_VAL(EPIT_CTRL_ADDR) |= CTRL_OCIEN;

}

/* Set interrupt interval, in milliseconds. */
void epit_set_interval(int interval)
{
    REG_VAL(EPIT_LOAD_ADDR) = (IPG_CLK_KHZ * interval) ;
    REG_VAL(EPIT_COMP_ADDR) = 0;
}

void epit_start_timer(void)
{
    REG_VAL(EPIT_STAT_ADDR) = 0x1;

    /* Enable timer */
    REG_VAL(EPIT_CTRL_ADDR) |= CTRL_EN;
}

static int count = 0;
void irq_handle(void)
{
    /* Clear status bit. */
    REG_VAL(EPIT_STAT_ADDR) = 0x1;
    irq_acknowledge();

    printf("EPIT time out...%d\n", count++);
}

int run(void)
{
    epit_init();
    epit_set_interval(1000);

    epit_start_timer();

    return 0;
}
