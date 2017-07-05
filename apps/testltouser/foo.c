/* @TAG(DATA61_BSD) */

#include <assert.h>
#include <stdio.h>

#ifdef NDEBUG
    #error "this test application needs assertions enabled"
#endif

/* Implemented in bar.c */
extern void *callee(void);

/* If LTO is working correctly, this function will be flattened. */
void caller(void) {
    void *f = callee();
    assert(f == __builtin_frame_address(0) &&
        "cross-file inlining not applied");
}

int run(void) {
    caller();
    printf("All OK\n");
    return 0;
}
