/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <assert.h>
#include <camkes.h>
#include "my_struct.h"
#include <stdio.h>
#include <string.h>

int run()
{
    /* First test calling the `refin` primitive function. */
    int x = 42;
    printf("%s: calling p_echo(&x) with x = %d\n", get_instance_name(), x);
    int result = p_echo(&x);
    printf("%s: result was %d\n", get_instance_name(), result);
    assert(result == x);

    /* Now test calling the `refin` complex function. */
    MyStruct a;
    for (unsigned int i = 0; i < sizeof(a.data) / sizeof(a.data[0]); i++) {
        a.data[i] = (int)i;
    }
    MyStruct b;
    memset(&b, 0, sizeof(b));
    printf("%s: calling c_echo(&a, &b) with a = {%d..%d}\n", get_instance_name(),
           a.data[0], a.data[sizeof(a.data) / sizeof(a.data[0]) - 1]);
    c_echo(&a, &b);
    printf("%s: result was b = {%d..%d}\n", get_instance_name(), b.data[0],
           b.data[sizeof(b.data) / sizeof(b.data[0]) - 1]);
    for (unsigned int i = 0; i < sizeof(a.data) / sizeof(a.data[0]); i++) {
        assert(a.data[i] == b.data[i]);
    }

    return 0;
}
