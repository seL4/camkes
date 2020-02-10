/*
 * Copyright 2020, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
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
