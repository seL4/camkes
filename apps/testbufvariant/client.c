/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <stdint.h>
#include <utils/util.h>

int run(void) {
    /* Test we can write something at an offset into our dataport that is
     * actually beyond what we declared, but should still be in the same pages.
     */
    printf("%s: Writing a number...\n", get_instance_name());
    *(volatile int*)((uintptr_t)d + PAGE_SIZE_4K + PAGE_SIZE_4K - 512) = 42;

    printf("%s: Switching to partner...\n", get_instance_name());
    s_switch_to();

    printf("All OK\n");

    return 0;
}
