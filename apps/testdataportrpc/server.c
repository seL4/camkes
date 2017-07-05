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

#include <assert.h>
#include <camkes.h>
#include <stddef.h>
#include <string.h>

static char *echo(const char *s) {
    char *p = strdup(s);
    assert(p != NULL);
    return p;
}

char *b_echo(const char *s) {
    return echo(s);
}

char *d_echo(const char *s) {
    return echo(s);
}

char *f_echo(const char *s) {
    return echo(s);
}

char *h_echo(const char *s) {
    return echo(s);
}

char *j_echo(const char *s) {
    return echo(s);
}
