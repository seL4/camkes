/* @TAG(NICTA_BSD) */

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
