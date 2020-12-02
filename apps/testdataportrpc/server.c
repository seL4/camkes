/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
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

char *f_echo(const char *s) {
    return echo(s);
}

char *h_echo(const char *s) {
    return echo(s);
}

char *j_echo(const char *s) {
    return echo(s);
}
