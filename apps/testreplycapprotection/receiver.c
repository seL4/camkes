/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdbool.h>
#include <stdio.h>

void a_switch_to(void)
{
    static bool not_first;

    while (not_first);

    printf("%s: Received call from Receiver\n", get_instance_name());

    /* OK, now let's proceed to try to trash our reply cap. You can more or
     * less read execution in a straight line from here as each function calls
     * the next.
     */

    printf("%s: Acquiring mutex...\n", get_instance_name());
    m_lock();

    printf("%s: Acquiring semaphore...\n", get_instance_name());
    s_wait();

    /* Trigger some more calls on the original endpoint, just in case this is
     * not correctly handled.
     */
    p1_emit();
    p2_emit();

    printf("%s: Taking first hop...\n", get_instance_name());
    b1_switch_to();

    printf("%s: Taking second hop...\n", get_instance_name());
    c1_switch_to();

    printf("%s: Taking third hop...\n", get_instance_name());
    d1_switch_to();

    printf("%s: Taking fourth (external) hop...\n", get_instance_name());
    e_switch_to();

    printf("%s: Releasing mutex...\n", get_instance_name());
    m_unlock();

    printf("%s: Releasing semaphore...\n", get_instance_name());
    s_post();

    printf("%s: Returning (moment of truth)...\n", get_instance_name());

    /* Prevent future output that can confuse users. */
    if (!not_first) {
        not_first = true;
    }
}

void b2_switch_to(void)
{
}

void c2_switch_to(void)
{
}

void d2_switch_to(void)
{
}
