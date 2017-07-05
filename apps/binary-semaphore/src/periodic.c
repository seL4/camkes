/* @TAG(DATA61_GPL) */

#include <camkes.h>

int run(void) {

    while (1) {
        ready_emit();
    }

    return 0;
}
