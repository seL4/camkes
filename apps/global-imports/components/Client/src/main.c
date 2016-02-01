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
#include <vec.h>
#include <shared_int.h>

int run(void) {
    char *str = g_get_string();
    p_print_string(str);
    vec_t vec = g_get_vec();
    p_print_vec(vec);

    printf("%d\n", counter->value);

    return 0;
}
