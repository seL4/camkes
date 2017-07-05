/* @TAG(NICTA_BSD) */

#include <stdlib.h>
#include <keyboard/keyboard.h>
#include <assert.h>

/* This code only provides very basic control of the keyboard controller. If
 * you are intending on extending this driver, more information about the
 * keyboard controller can be found at
 * http://www.win.tue.nl/~aeb/linux/kbd/scancodes-11.html.
 * This driver takes complete control of both ps/2 ports, and assumes that the keyboard
 * is attached to the first port. It places the keyboard in mode 2 scancode generator
 */

/* Directives can be written to this IO port to inform the keyboard controller
 * of how your next write to one of the keyboard ports should be interpreted.
 */
#define KEYBOARD_INPUT_CONTROL      0x64

/* This byte can be written to port KEYBOARD_INPUT_CONTROL to tell the keyboard
 * controller that the next byte you write to port KEYBOARD_OUTPUT_BUFFER
 * should be interpreted as a write to the Controller Command Byte.
 */
#define KEYBOARD_CONTROL_WRITE_CCB  0x60

/* This IO port can be written to in order to pass data to the keyboard
 * controller. Its data is interpreted differently depending on what you
 * previously wrote to the port KEYBOARD_INPUT_CONTROL. It can be read from to
 * get the last character received from the keyboard.
 */
#define KEYBOARD_OUTPUT_BUFFER      0x60

/* The following values can be written to the Controller Command Byte to enable
 * or disable keyboard interrupt delivery respectively. Without interrupts
 * enabled, the controller registers need to be polled for input which is not
 * ideal. Note that every bit in the Controller Command Byte is significant and
 * so these writes may have unintended side-effects if you are using this
 * driver in combination with, say a mouse driver. If this is the case I
 * suggest you improve this driver to read the CCB before writing to it in
 * order to only modify bit 0.
 */
#define KEYBOARD_CCB_IRQ_ENABLE     0x01
#define KEYBOARD_CCB_IRQ_DISABLE    0x00

static in8_fn io_in8;
static out8_fn io_out8;

static inline uint8_t ps2_poll_output(void) {
    return io_in8(KEYBOARD_OUTPUT_BUFFER);
}

static uint8_t _ps2_read_control(void) {
    return io_in8(KEYBOARD_INPUT_CONTROL);
}

static inline uint8_t ps2_read_output(void) {
    while( (_ps2_read_control() & 0x1) == 0);
    return ps2_poll_output();
}

/* some helper macros for manipulating io ports
 * your opinion on macros may vary. but the goal is to make the keyboard setup code look somewhat
 * readable */
#define ps2_single_control(byte) io_out8(KEYBOARD_INPUT_CONTROL, byte)
#define ps2_dual_control(byte1, byte2) do {ps2_single_control(byte1);io_out8(KEYBOARD_CONTROL_WRITE_CCB, byte2);} while(0)
#define ps2_write_output(byte) io_out8(KEYBOARD_OUTPUT_BUFFER, byte)

void keyboard_init(int enable_interrupt, in8_fn in8, out8_fn out8) {
    io_in8 = in8;
    io_out8 = out8;

    int error;
    uint8_t config;
    /* initialize the keyboard */
    //disable both ps2 devices
    ps2_single_control(0xAD);
    ps2_single_control(0xA7);
    // flush the output buffer by reading and discarding
    ps2_poll_output();
    // get old internal configuration
    ps2_single_control(0x20);
    config = ps2_read_output();
    // disable irqs and translation (bits 0, 1, 6)
    config &= 0xBC;
    ps2_dual_control(0x60, config);
    // perform a test
    ps2_single_control(0xAA);
    error = ps2_read_output();
    assert(error == 0x55);
    // test port
    ps2_single_control(0xAB);
    error = ps2_read_output();
    assert(error == 0x00);
    // enable port
    ps2_single_control(0xAE);
    if (enable_interrupt) {
        config |= 0x1;
        ps2_dual_control(0x60, config);
    }
    // switch to mode 2 scancode
    ps2_write_output(0xf0);
    ps2_write_output(2);
    error = ps2_read_output();
    assert(error == 0xfa);
}

void keyboard_reset() {
    uint8_t config;
    /* disable ports and interrupts */
    // get old internal configuration
    ps2_single_control(0x20);
    config = ps2_read_output();
    config &= 0xBC;
    ps2_dual_control(0x60, config);
    //disable both ps2 devices
    ps2_single_control(0xAD);
    ps2_single_control(0xA7);
}

int keyboard_get_scancode(int *scancode) {
    /* see if there is a waiting scancode */
    if( (_ps2_read_control() & 0x1) == 0) {
        return 0;
    }
    *scancode = ps2_poll_output();
    return 1;
}
