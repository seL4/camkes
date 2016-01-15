/*
 * Copyright 2015, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <camkes.h>
#include <string.h>

void i__init(void) {
}

char * i_echo_string(const char *s) {
    return strdup(s);
}

int i_echo_int(int i) {
    return i;
}

float i_echo_float(float f) {
    return f;
}

double i_echo_double(double d) {
    return d;
}

int i_echo_mix(double d) {
    return d;
}

int i_echo_parameter(int pin, int *pout) {
    *pout = pin;
    return pin;
}

