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
#include <vec.h>

void getter__init(void) {
    counter->value = 0;
}

char * getter_get_string(void) {
    counter->value++;
    return strdup("Hello, World!\n");
}

vec_t getter_get_vec(void) {
    counter->value++;
    return (vec_t) {.x = 4.0, .y = 2.0};
}
