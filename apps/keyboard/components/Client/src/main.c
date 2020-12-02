/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
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

