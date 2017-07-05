/* @TAG(DATA61_BSD) */

#include <autoconf.h>

/* Writes the current value in xmm0 to the stack, then reads it back.
 * This function should cause a general protection fault if the stack
 * is not correctly aligned. */
.global movaps_test
movaps_test:
    /* Align the stack to 16 bytes assuming:
     * - 16 byte stack alignment before this function was called
     * - the register-sized return address has been pushed by the
     *   call and nothing else
     */
    #define STACK_OFFSET_BYTES $(16 - (CONFIG_WORD_SIZE / 8))
    sub STACK_OFFSET_BYTES, %esp

    /* Push and pop the %xmm0 */
    sub $16, %esp
    movdqa %xmm0, (%esp)
    movdqa (%esp), %xmm0
    add $16, %esp

    /* Compensate for stack alignment */
    add STACK_OFFSET_BYTES, %esp

    ret
