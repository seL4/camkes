/* @TAG(NICTA_BSD) */

#include <assert.h>
#include <camkes.h>
#include <stddef.h>
#include <stdint.h>

void p_post(dataport_ptr_t ptr) {
    assert(ptr.id != -1);
    volatile int *x = dataport_unwrap_ptr(ptr);
    assert(x != NULL);
    assert(*x == 42);
}
