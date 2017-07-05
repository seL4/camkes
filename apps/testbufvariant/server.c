/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <stdint.h>
#include <utils/util.h>

void s_switch_to(void) {
    /* Test that we can read what the client wrote. */
    while (*(volatile int*)((uintptr_t)d + PAGE_SIZE_4K + PAGE_SIZE_4K - 512) != 42);
}
