/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <stdio.h>

int run(void) {
    printf("%s: starting...\n", get_instance_name());
    l_lock();
    printf("%s: got lock!\n", get_instance_name());
    l_unlock();
    printf("%s: released\n", get_instance_name());
    return 0;
}
