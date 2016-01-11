/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 */

#ifndef _KEYBOARD_CODES_H_
#define _KEYBOARD_CODES_H_

/* Convert a keyboard scan code (from set 2) to its character representation.
 * Returns 0 for anything that is not a scan code for a canonical character.
 */
char keyboard_code_to_char(int index);

#endif
