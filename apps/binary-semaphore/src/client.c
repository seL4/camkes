/* @TAG(DATA61_GPL) */

#include <stdio.h>
#include <camkes.h>

#define TO_ECHO 42

int run(void) {

    printf("Echoing: %d == %d\n", TO_ECHO, echo_echo(TO_ECHO));

    return 0;
}
