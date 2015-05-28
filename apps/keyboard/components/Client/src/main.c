/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

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

