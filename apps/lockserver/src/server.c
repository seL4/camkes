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

void a_lock(void) {
    (void)m_lock();
}

void a_unlock(void) {
    (void)m_unlock();
}

void b_lock(void) {
    (void)m_lock();
}

void b_unlock(void) {
    (void)m_unlock();
}

void c_lock(void) {
    (void)m_lock();
}

void c_unlock(void) {
    (void)m_unlock();
}
