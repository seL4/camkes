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

void l__init(void) {
}

static struct {
    const char *key;
    const char *value;
} dict[] = {
    {
        .key = "foo",
        .value = "bar",
    },
    {
        .key = "secret",
        .value = "baz",
    }
};

/* Lookup and return the value associated with 'key' */
char *l_get_value(const char *key) {
    for (unsigned int i = 0; i < sizeof(dict) / sizeof(dict[0]); ++i) {
        if (!strcmp(key, dict[i].key)) {
            return strdup(dict[i].value);
        }
    }
    /* Not found */
    return strdup("");
}
