/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stddef.h>

/* Uncomment the following to see compile-time warnings, resulting from calling
 * these unimplemented functions.
 */
#if 0
void foo(void) {
    e_wait();
}

void bar(void) {
    e_poll();
}

void baz(void) {
    e_reg_callback(NULL, NULL);
}
#endif

void e_handle(void) {
    /* Interrupt handler. */
    e_acknowledge();
}

int run(void) {
  for(;;);
}
