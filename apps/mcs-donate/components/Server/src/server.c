/*
 * Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <string.h>

/* Number of clients connected to this server */
#define NUM_CLIENTS 2

/* Number of clients that have made their last call (echo_parameter) */
static int clients_done;

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

    /* Report success from the server (higher priority) to avoid interleaved output. */
    clients_done++;
    if (clients_done == NUM_CLIENTS) {
        printf("All clients done\n");
    }

    return pin;
}

