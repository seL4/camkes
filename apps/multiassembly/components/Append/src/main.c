/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <camkes.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 128

void i_process(const char *str) {
    char buf[BUF_SIZE];
    snprintf(buf, BUF_SIZE, "%s%s", str, string_to_append);

    o_process(buf);
}
