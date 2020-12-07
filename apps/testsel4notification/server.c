/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

/* Server of seL4Notification testing application. The only thing we implement here
 * is a function to effectively expose `e_emit` to our client.
 */

#include <camkes.h>

void n_notify_me(void)
{
    e_emit();
}
