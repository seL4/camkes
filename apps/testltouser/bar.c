/* @TAG(DATA61_BSD) */

/* If LTO is working correctly, this function will be inlined into its caller.
 */
void *callee(void) {
    return __builtin_frame_address(0);
}
