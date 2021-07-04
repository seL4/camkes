/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <stdlib.h>
#include <camkes/debug.h>

int global_number = 34;

int run()
{
    const char *shello = "hello world";
    const char *smore = "a longer string that will overflow the message registers on ARM";
    char *s;
    int i = 42, j;
    int p, p1, p2;
    float f = 273421.4274, g;
    double d = 273421.4274, e;

    printf("Starting the client\n");
    printf("-------------------\n");
    camkes_software_breakpoint();
    j = a_echo_int(i);
    printf("echo_int: %d -> %d\n", i, j);

    g = a_echo_float(f);
    printf("echo_float: %f -> %f\n", f, g);

    e = a_echo_double(d);
    printf("echo_double: %f -> %f\n", d, e);
    camkes_software_breakpoint();

    j = a_echo_mix(d);
    printf("echo_mix: %f -> %d\n", d, j);

    s = a_echo_string(shello);
    printf("echo_string: \"%s\" -> \"%s\"\n", shello, s);
    free(s);

    global_number = 50;
    s = a_echo_string(smore);
    printf("echo_string: \"%s\" -> \"%s\"\n", smore, s);
    free(s);
    printf("%d\n", global_number);

    p = 123;
    p2 = a_echo_parameter(p, &p1);
    printf("echo_parameter: %d -> %d (returned = %d)\n", p, p1, p2);

    p = 100;
    a_increment_parameter(&p);
    printf("increment_parameter: 100 -> %d\n", p);

    printf("After the client\n");
    return 0;
}
