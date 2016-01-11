/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <camkes.h>
#include <string.h>

void b__init(void) {
}

char * b_echo_string(const char *s) {
    return strdup(s);
}

int b_echo_int(int i) {
    return i;
}

float b_echo_float(float f) {
    return f;
}

double b_echo_double(double d) {
    return d;
}

int b_echo_mix(double d) {
    return d;
}

int b_echo_parameter(int pin, int *pout) {
    *pout = pin;
    return pin;
}

void b_increment_parameter(int *x) {
    *x = *x + 1;
}
