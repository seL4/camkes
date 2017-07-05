/* @TAG(DATA61_BSD) */

/* Usage of the keyboard in this file is based on information from
 * http://www.win.tue.nl/~aeb/linux/kbd/scancodes-11.html
 */

#include <stdio.h>
#include <camkes.h>

#define KEYBOARD_STATUS_PORT    0x64 /* Control port. */
#define KEYBOARD_DATA_PORT      0x60 /* Input/output port. */

#define KEYBOARD_CCB_WRITE	0x60 /* Write it to the Control port before write a CCB. */
#define KEYBOARD_CCB_READ	0x20 /* Write it to the Control port before read a CCB. */

#define KEYBOARD_ENABLE		0xae /* Keyboard enable command. */
#define KEYBOARD_DISABLE	0xad /* Keyboard disable command. */

static uint8_t read_status(void)
{
	char c;
	c = s_in8(KEYBOARD_STATUS_PORT);

	printf("Current Status: 0x%x\n", c);
	return c;
}

static uint8_t read_scancode(void)
{
	return s_in8(KEYBOARD_DATA_PORT);
}

static int keyboard_enable(void)
{
	s_out8(KEYBOARD_STATUS_PORT, KEYBOARD_ENABLE);
	return 0;
}

void interrupt_handle(void)
{
	printf("Scancode: %u\n", read_scancode());
	keypress_emit();
    interrupt_acknowledge();
}

void kbd__init(void)
{
	read_status();
	keyboard_enable();
}

int kbd_get_scancode(void)
{
	return read_scancode();
}
