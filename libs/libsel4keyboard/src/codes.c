/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 */

#include <keyboard/codes.h>

/* Mapping from scan codes to characters. Anything that is not a definitive
 * character is mapped to 0. Note that this assumes set 2 scan codes.
 */
static char codes[255] = {
    [0x16] = '1', // or !
    [0x1e] = '2', // or @
    [0x26] = '3', // or #
    [0x25] = '4', // or $
    [0x2e] = '5', // or %
    [0x36] = '6', // or ^
    [0x3d] = '7', // or &
    [0x3e] = '8', // or *
    [0x46] = '9', // or (
    [0x45] = '0', // or )
    [0x66] = '\b',
    [0x0d] = '\t',
    [0x15] = 'Q',
    [0x1d] = 'W',
    [0x24] = 'E',
    [0x2d] = 'R',
    [0x2c] = 'T',
    [0x35] = 'Y',
    [0x3c] = 'U',
    [0x43] = 'I',
    [0x44] = 'O',
    [0x4d] = 'P',
    [0x54] = '[', // or {
    [0x5b] = ']', // or }
    [0x5d] = '\\', //or |
    [0x1c] = 'A',
    [0x1b] = 'S',
    [0x23] = 'D',
    [0x2b] = 'F',
    [0x34] = 'G',
    [0x33] = 'H',
    [0x3b] = 'J',
    [0x42] = 'K',
    [0x4b] = 'L',
    [0x4c] = ';', // or :
    [0x52] = '\'', // or "
    [0x5a] = '\n', // enter
    [0x1a] = 'Z',
    [0x22] = 'X',
    [0x21] = 'C',
    [0x2a] = 'V',
    [0x32] = 'B',
    [0x31] = 'N',
    [0x3a] = 'M',
    [0x41] = ',', // or <
    [0x49] = '.', // or >
    [0x4a] = '/', // or ?
    [0x29] = ' ', // space
    [0x76] = 033, // esc
};

char keyboard_code_to_char(int index) {
    if (index > sizeof(codes) || index < 0) {
        return 0;
    }
    return codes[index];
}
