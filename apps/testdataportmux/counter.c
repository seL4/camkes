/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <assert.h>
#include <camkes.h>
#include <stdio.h>

int run(void) {
#ifdef NDEBUG
    printf("WARNING: assertions are disabled!\n");
#endif

    volatile int *value = (volatile int*)port;

    while (*value < 20) {
        /* Wait for our turn. */
        while ((*value) % 5 != ID);

        int oldval = *value;

        printf("%d: My turn to increment (current value %d)\n", ID, oldval);

        /* Pause a while to try to expose any race conditions. */
        for (unsigned int i = 0; i < 100000; i++) {
            asm volatile ("");
        }

        /* Now we should be able to atomic increment with no error. */
        bool result = __sync_bool_compare_and_swap(value, oldval, oldval + 1);
        assert(result);
    }

    /* Only ID == 4 will probably reach this point though, depending on
     * scheduling, others may.
     */
    if (ID == 4) {
        printf("%d: We're done, people\n", ID);
    }

    return 0;
}
