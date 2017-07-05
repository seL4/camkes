/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
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

