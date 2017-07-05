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
#include <stdint.h>
#include <stdio.h>
#include "util.h"

/* Number of bytes in a MAC address. */
#define SIZEOF_MAC (48 / 8)

uint64_t make_mac(const char *data) {
    uint64_t x = 0;

    /* Consume bytes from the input string until we've exhausted it and then
     * just pad the rest of the MAC with 0s.
     */
    for (unsigned int i = 0; i < SIZEOF_MAC; i++) {
        if (*data == '\0') {
            x <<= 8;
        } else {
            x = (x << 8) | (uint64_t)(*data);
            data++;
        }
    }
    return x;
}

/* Note that MAC addresses are stored big endian and IP addresses are stored
 * little endian. Only chosen this way to make construction simpler.
 */

void mac_to_string(uint64_t input, char *output) {
    sprintf(output, "%02x:%02x:%02x:%02x:%02x:%02x",
        (unsigned int)(input & 0xff), (unsigned int)((input >> 8) & 0xff),
        (unsigned int)((input >> 16) & 0xff),
        (unsigned int)((input >> 24) & 0xff),
        (unsigned int)((input >> 32) & 0xff),
        (unsigned int)((input >> 40) & 0xff));
}

void ip_to_string(uint32_t input, char *output) {
    sprintf(output, "%u.%u.%u.%u", input >> 24, (input >> 16) & 0xff,
        (input >> 8) & 0xff, input & 0xff);
}
