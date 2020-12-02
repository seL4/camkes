/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <payload.h>

void a_calculate(payload_t *data)
{
    const char *name = get_instance_name();
    data->result = 0;
    for (int i = 0; i < data->sz; i++) {
        printf("%s: Adding %d\n", name, data->operands[i]);
        data->result += data->operands[i];
    }
}
