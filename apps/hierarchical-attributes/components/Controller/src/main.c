/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <camkes.h>
#include <stdio.h>

int run(void) {

    printf("Foo\n");
    foo_pa_print_attributes();

    printf("Foo Bar\n");
    foo_nested_pa0_print_attributes();

    printf("Foo Bar Baz\n");
    foo_nested_pa1_print_attributes();
    
    printf("Foo Baz\n");
    foo_nested_pa2_print_attributes();

    return 0;
}
