/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <stdio.h>

#include "common.h"

void b_f(void) {
    printf("Server is testing alignment...\n");
    test_alignment();
}
