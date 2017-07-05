/* @TAG(DATA61_BSD) */

#ifndef _KEYBOARD_CODES_H_
#define _KEYBOARD_CODES_H_

/* Convert a keyboard scan code (from set 2) to its character representation.
 * Returns 0 for anything that is not a scan code for a canonical character.
 */
char keyboard_code_to_char(int index);

#endif
