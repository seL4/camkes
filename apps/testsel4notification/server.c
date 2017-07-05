/* @TAG(NICTA_BSD) */

/* Server of seL4Notification testing application. The only thing we implement here
 * is a function to effectively expose `e_emit` to our client.
 */

#include <camkes.h>

void n_notify_me(void) {
    e_emit();
}
