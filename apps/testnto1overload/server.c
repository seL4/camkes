/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <assert.h>
#include <camkes.h>
#include <sel4/sel4.h>
#include <stdbool.h>
#include <stdio.h>

extern seL4_Word f_get_badge(void);

void f_foo(void) {
    static seL4_Word badge;
    static bool not_first;
    if (!not_first) {
        badge = f_get_badge();
        not_first = true;
    } else {
        seL4_Word new_badge = f_get_badge();
        assert(new_badge != badge);
        if (new_badge != badge) {
            printf("All OK\n");
        }
    }
}
