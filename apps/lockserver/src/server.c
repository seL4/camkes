/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
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
