/* @TAG(NICTA_BSD) */

#include <camkes.h>
#include <stddef.h>

/* Uncomment the following to see compile-time warnings, resulting from calling
 * these unimplemented functions.
 */
#if 0
void foo(void) {
    e_wait();
}

void bar(void) {
    e_poll();
}

void baz(void) {
    e_reg_callback(NULL, NULL);
}
#endif

void e_handle(void) {
    /* Interrupt handler. */
    e_acknowledge();
}
