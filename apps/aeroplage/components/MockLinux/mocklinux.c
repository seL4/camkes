/* @TAG(DATA61_BSD) */

/* CAmkES provides a generated header that prototypes all the relevant
 * generated symbols.
 */
#include <camkes.h>

#include <ringbuffer/ringbuffer.h>
#include <stdbool.h>
#include <stdlib.h>

/* This function is invoked by the main CAmkES thread in this component. */
int run(void) {
    ringbuffer_t *input = rb_new((void*)keyboard_input, sizeof(*keyboard_input));
    if (input == NULL) {
        abort();
    }

    ringbuffer_t *output = rb_new((void*)framebuffer, sizeof(*framebuffer));
    if (output == NULL) {
        abort();
    }

    /* Obviously a real Linux would be doing more than just passing through
     * characters here. In particular, network communication.
     */
    while (true) {
        char c = (char)rb_receive_byte(input);
        rb_transmit_byte(output, (unsigned char)c);
    }

    return 0;
}
