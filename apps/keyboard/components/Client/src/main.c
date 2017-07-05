/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <stdio.h>

static void keyboard_event_callback(void *arg)
{
	int key = kbd_get_scancode();
	printf("Key Pressed: %d\n", key);

	keypress_reg_callback(&keyboard_event_callback, NULL);
}

int run(void)
{
	printf("Register keyboard driver event.\n");

	keypress_reg_callback(&keyboard_event_callback, NULL);
	return 0;
}

