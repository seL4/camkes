/*
 * Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <string.h>

void i__init(void)
{
}

char *i_echo_string(const char *s)
{
    return strdup(s);
}

int i_echo_int(int i)
{
    return i;
}

float i_echo_float(float f)
{
    return f;
}

double i_echo_double(double d)
{
    return d;
}

int i_echo_mix(double d)
{
    return d;
}

int i_echo_parameter(int pin, int *pout)
{
    *pout = pin;
    return pin;
}

