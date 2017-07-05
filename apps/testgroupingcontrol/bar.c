/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <stdio.h>

static unsigned ping_count;

void p_ping(void) {
    ping_count++;
    if (ping_count == 2) {
        printf("All OK\n");
    } else if (ping_count > 2) {
        printf("FAIL\n");
    }
}
