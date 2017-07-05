/* @TAG(NICTA_BSD) */

#include <assert.h>
#include <camkes.h>
#include <stdint.h>
#include <stdio.h>

int run(void) {
#ifdef NDEBUG
    printf("WARNING: assertions are disabled!\n");
#endif

    volatile int *x = (volatile int*)((uintptr_t)d + 16);
    *x = 42;
    dataport_ptr_t ptr = dataport_wrap_ptr((void*)x);
    assert(ptr.id != -1);
    p_post(ptr);

    printf("All OK\n");

    return 0;
}
