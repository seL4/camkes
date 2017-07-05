/* @TAG(DATA61_BSD) */

/* CAmkES provides a generated header that prototypes all the relevant generated
 * symbols.
 */
#include <camkes.h>

#include <keyboard/codes.h>
#include <keyboard/keyboard.h>
#include <ringbuffer/ringbuffer.h>
#include <utils/util.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

static uint8_t in8(uint16_t port) {
    return ports_in8(port);
}

static void out8(uint16_t port, uint8_t value) {
    ports_out8(port, value);
}

int run(void) {
    keyboard_init(0, in8, out8);

    ringbuffer_t *output = rb_new((void*)char_out, sizeof(*char_out));
    if (output == NULL) {
        abort();
    }

    /* Take each received character and pass it on to the switch. */
    while (true) {
        int c;

        /* do basic tracking of multi byte sequences */
        static int escape_code = 0;
        static int escape_state = 0;
        static int break_code = 0;

        while(!keyboard_get_scancode(&c));

        /* first parse escape codes etc */
        switch (c) {
            case 0xf0:
                break_code = 0xf0;
                continue;
            case 0xe0:
            case 0xe1:
                escape_code = c;
                escape_state = 0;
                continue;
            default:
                /* need to do actual parsing */
                switch(escape_code) {
                    case 0xe1:
                        /* need to ignore two scancodes */
                        escape_state++;
                        if (escape_state == 2) {
                            escape_code = 0;
                            break_code = 0;
                        }
                        continue;
                    case 0xe0:
                        /* key down */
                        break_code = 0;
                        escape_code = 0;
                        continue;
                    default:
                        if (!break_code) {
                            break_code = 0;
                            escape_code = 0;
                            continue;
                        }
                        /* key up */
                        break_code = 0;
                        escape_code = 0;
                        break;
                }
                break;
        }

        char c1 = keyboard_code_to_char(c);
        if (c1 != 0) {
            rb_transmit_byte(output, (unsigned char)c1);
        }
    }

    return 0;
}
