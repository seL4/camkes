/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <string.h>

void external__init(void) {}

char *external_get_value(const char *key) {
    if (!strcmp(key, "secret")) {
        /* Block reading the value of "secret" */
        return strdup("");
    } else {
        /* Allow anything else */
        return backing_get_value(key);
    }
}
