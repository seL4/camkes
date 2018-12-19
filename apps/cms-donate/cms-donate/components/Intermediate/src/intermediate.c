/*
 * Copyright 2018, Data61
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

void r__init(void) {
}

char * r_echo_string(const char *s) {
    return i_echo_string(s);
}

int r_echo_int(int i) {
    return i_echo_int(i);
}

float r_echo_float(float f) {
    return i_echo_float(f);
}

double r_echo_double(double d) {
    return i_echo_double(d);
}

int r_echo_mix(double d) {
    return i_echo_mix(d);
}

int r_echo_parameter(int pin, int *pout) {
    return i_echo_parameter(pin, pout);
}

