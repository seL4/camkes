/* @TAG(DATA61_BSD) */

#include <camkes.h>

int run(void) {
    p_wait();
    t_switch_to();
    return 0;
}
