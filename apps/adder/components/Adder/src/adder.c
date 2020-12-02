/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <camkes/dataport.h>
#include "payload.h"

dataport_ptr_t a_calculate(dataport_ptr_t ptr) {
    struct payload *p1, *p2;
    p1 = (struct payload*)dataport_unwrap_ptr(ptr);
    p2 = (struct payload*)((void*)d + 2048);
    const char *name = get_instance_name();
    p2->result = 0;
    for (int i = 0; i < p1->sz; i++) {
        printf("%s: Adding %d\n", name, p1->operands[i]);
        p2->result += p1->operands[i];
    }
    return dataport_wrap_ptr((void*)p2);
}
