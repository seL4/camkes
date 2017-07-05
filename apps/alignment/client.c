/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <stdio.h>

#include "common.h"

int run() {
    printf("Calling server...\n");
    a_f();
    printf("Back from server!\n");
    printf("Client is testing alignment...\n");
    test_alignment();
    printf("All is well in the universe!\n");

    return 0;
}
