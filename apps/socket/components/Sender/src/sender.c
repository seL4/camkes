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

#include <camkes.h>
#include <stdio.h>
#include <string.h>
#include <sync/spinlock.h>

int run(void) {
    const char *s = "hello world";
    const char *name = get_instance_name();

    printf("%s: Initialising lock...\n", name);
    sync_spinlock_init((sync_spinlock_t*)&sock->lock);

    printf("%s: Notifying transport...\n", name);
    init_emit();

    printf("%s: Writing \"%s\"...\n", name, s);
    sync_spinlock_lock((sync_spinlock_t*)&sock->lock);
    strcpy((char*)sock->data, s);
    sock->full = 1;
    sync_spinlock_unlock((sync_spinlock_t*)&sock->lock);

    printf("%s: Done.\n", name);
    return 0;
}
