/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

/* Server of seL4Notification testing application. The only thing we implement here
 * is a function to effectively expose `e_emit` to our client.
 */

#include <camkes.h>

void n_notify_me(void) {
    e_emit();
}
