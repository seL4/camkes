/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

/* Server of seL4Notification testing application. The only thing we implement here
 * is a function to effectively expose `e_emit` to our client.
 */

#include <camkes.h>

void n_notify_me(void) {
    e_emit();
}
