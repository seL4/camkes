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
#include <stdio.h>

int run() {
    unsigned int i, j;
    unsigned char k;

    printf("Starting the client\n");
    printf("-------------------\n");

    h_hello();

    h_input(100);

    h_multi_input(100, 200);

    i = h_ret();

    printf("Hello_ret: %d\n", i);

    h_output(&i);

    printf("Hello_output: %d\n", i);

    i = 100;
    printf("Hello_in_out: %d", i);
    h_in_out(&i);
    printf("-> %d\n", i);

    i = h_rainbow(100, 200, &j, &k);
    printf("Hello_rainbow: (%d, %d) -> %d (%d, %d)\n", 100, 200, i, j, k);

    h_input_string("Hello CakeML!");

    h_input_strings("Foo!", "Bar!");

    char * input_str = "Hello world";
    char * reversed = h_reverse_string(input_str);
    printf("Hello_reverse_string: \"%s\" -> \"%s\"\n", input_str, reversed);

    g_bye();
    return 0;
}
