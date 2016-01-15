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
#include <stdio.h>
#include <stdlib.h>

int run() {
    char *shello = "hello world";
    char *s;
    int i = 42, j;
    int p, p1, p2;
    float f = 273421.4274, g;
    double d = 273421.4274, e;

    printf("Starting the %s\n", get_instance_name());
    printf("-------------------\n");

    j = i_echo_int(i);
    printf("echo_int: %d -> %d\n",i, j);

    g = i_echo_float(f);
    printf("echo_float: %f -> %f\n",f, g);

    e = i_echo_double(d);
    printf("echo_double: %f -> %f\n",d, e);

    j = i_echo_mix(d);
    printf("echo_mix: %f -> %d\n",d, j);

    s = i_echo_string(shello);
    printf("echo_string: \"%s\" -> \"%s\"\n", shello, s);
    free(s);

    p2 = i_echo_parameter(p, &p1);
    printf("echo_parameter: %d -> %d (returned = %d)\n", p, p1, p2);

    printf("After the %s\n", get_instance_name());
    return 0;
}
