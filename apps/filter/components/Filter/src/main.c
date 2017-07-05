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
