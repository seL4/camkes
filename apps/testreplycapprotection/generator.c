/* @TAG(NICTA_BSD) */

#include <camkes.h>
#include <stdio.h>

int run(void) {
    printf("%s: Calling Receiver...\n", get_instance_name());
    a_switch_to();

    printf("All OK\n");

    return 0;
}
