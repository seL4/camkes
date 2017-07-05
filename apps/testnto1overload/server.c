/* @TAG(NICTA_BSD) */

#include <assert.h>
#include <camkes.h>
#include <sel4/sel4.h>
#include <stdbool.h>
#include <stdio.h>

void f_foo(void) {
    static seL4_Word badge;
    static bool not_first;
    if (!not_first) {
        badge = f_get_sender_id();
        not_first = true;
    } else {
        seL4_Word new_badge = f_get_sender_id();
        assert(new_badge != badge);
        if (new_badge != badge) {
            printf("All OK\n");
        }
    }
}
