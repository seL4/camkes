/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include "driver.h"

int run(void) {
    uart_put("hello from ");
    uart_put(get_instance_name());
    uart_put_char('\n');
    h_handoff();
    return 0;
}
