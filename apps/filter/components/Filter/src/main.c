/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <Filter.h>
#include <string.h>

void external__init(void) {}

char *external_get_value(char *key) {
    if (!strcmp(key, "secret")) {
        /* Block reading the value of "secret" */
        return "";
    } else {
        /* Allow anything else */
        return backing_get_value(key);
    }
}
