/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <string.h>


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
