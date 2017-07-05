/* @TAG(DATA61_BSD) */

#ifndef _LIBKEYBOARD_KEYBOARD_H_
#define _LIBKEYBOARD_KEYBOARD_H_

#include <stdint.h>

/* The IRQ number for the keyboard. If you initialize the controller with
 * interrupts then this is the irq number they will appear on */
#define KEYBOARD_IRQ 1

/* Callbacks used below. */
typedef uint8_t (*in8_fn)(uint16_t port);
typedef void (*out8_fn)(uint16_t port, uint8_t value);

/* Initialise the driver.
 *  enable_interrupt - Set the keyboard controller to generate interrupts
 *      when scancodes are generated.
 *  in8 - Function for getting a byte from either IO port 0x60 or port 0x64.
 *  out8 - Function for writing a byte to either IO port 0x60 or port 0x64.
 */
void keyboard_init(int enable_interrupt, in8_fn in8, out8_fn out8);

/* Disable the keyboard device (which may or may not have been its initial state)
 */
void keyboard_reset(void);

/* Read a scancode. Returns 0 if there wasn't one.
 *  scancode - Location to store the read scancode
 */
int keyboard_get_scancode(int *scancode);

#endif /* !_LIBKEYBOARD_KEYBOARD_H_ */
