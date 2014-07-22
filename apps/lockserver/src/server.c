/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <Server.h>

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
