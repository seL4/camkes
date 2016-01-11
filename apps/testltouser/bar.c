/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

/* If LTO is working correctly, this function will be inlined into its caller.
 */
void *callee(void) {
    return __builtin_frame_address(0);
}
