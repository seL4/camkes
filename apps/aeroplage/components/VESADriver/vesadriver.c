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

/* CAmkES provides a generated header that prototypes all the relevant
 * generated symbols.
 */
#include <camkes.h>

#include <assert.h>
#include <bga/bga.h>
#include <ringbuffer/ringbuffer.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* The following code drives the Bochs Graphics Array (BGA) video device to
 * display the various components of the multilevel terminal. Note that it only
 * uses libsel4bga's simple interface (bga_set_pixel). In a real, performant
 * system we would enable raw access to the frame buffer and memcpy directly
 * into it or use banked mode. For more information about the BGA:
 *  http://wiki.osdev.org/Bochs_VBE_Extensions
 */

/* Opaque pointer to the Bochs Graphics Array (VESA device) meta data. */
static bga_p bga;

/* Provided in the generated chars.c */
extern char *to_pixels(char c);

/* Pixel dimensions of a character's XBM representation. See chars.sh or
 * chars.c.
 */
#define CHAR_WIDTH 14
#define CHAR_HEIGHT 26

/* Draw a single character on the screen at (x, y). */
static void draw(unsigned int x, unsigned int y, char c) {
    /* Get the character's XBM representation. */
    char *pixels = to_pixels(c);
    assert(pixels != NULL);

    char white[] = { 255, 255, 255 };
    char black[] = { 0, 0, 0 };

    /* Slightly messy row calculation because the XBM format dictates that the
     * row is padded to a byte boundary.
     */
    unsigned int row_width = CHAR_WIDTH;
    if (row_width % 8 != 0) {
        row_width += 8 - row_width % 8;
    }

    /* Write the representation out to the screen with white filled pixels and
     * black empty pixels.
     */
    for (unsigned int i = 0; i < CHAR_HEIGHT; i++) {
        for (unsigned int j = 0; j < CHAR_WIDTH; j++) {
            char block = pixels[(j + i * row_width) / 8];
            unsigned int offset = (j + i * row_width) % 8;
            bga_set_pixel(bga, x + j, y + i,
                (block & (1 << offset)) ? white: black);
        }
    }
}

/* Draw a string on the screen starting at (x, y). */
static void draw_string(unsigned int x, unsigned int y, const char *s) {
    while (*s != '\0') {
        draw(x, y, *s++);
        x += CHAR_WIDTH;
    }
}

/* Width and height of the domain windows. */
#define WIDTH 312
#define HEIGHT 300

/* Draw coloured borders around each input's virtual framebuffer. */
static void borders(void) {
    char purple[] = { 210, 101, 141 };
    char blue[] = { 197, 103, 0 };

    /* The below is full of magic numbers, but they're all basically pixel
     * tweaks to make sure lines and headings look semi-natural.
     */

    for (unsigned int i = 100; i < 100 + WIDTH; i++) {
        for (unsigned int j = 100; j < 100 + 4 + CHAR_HEIGHT; j++) {
            bga_set_pixel(bga, i, j, purple);
        }
        bga_set_pixel(bga, i, 100 + HEIGHT, purple);
    }
    for (unsigned int i = 100; i < 100 + HEIGHT; i++) {
        bga_set_pixel(bga, 100, i, purple);
        bga_set_pixel(bga, 100 + WIDTH, i, purple);
    }
    draw_string(100 + 100 + 2 * CHAR_WIDTH, 102, "Low");

    for (unsigned int i = 200 + WIDTH; i < 200 + 2 * WIDTH; i++) {
        for (unsigned int j = 100; j < 100 + 4 + CHAR_HEIGHT; j++) {
            bga_set_pixel(bga, i, j, blue);
        }
        bga_set_pixel(bga, i, 100 + HEIGHT, blue);
    }
    for (unsigned int i = 100; i < 100 + HEIGHT; i++) {
        bga_set_pixel(bga, 200 + WIDTH, i, blue);
        bga_set_pixel(bga, 200 + 2 * WIDTH, i, blue);
    }
    draw_string(200 + WIDTH + 100 + 2 * CHAR_WIDTH, 102, "High");
}

/* Return true if we're capable of displaying this character. */
static bool printable(char c) {
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c == ' ') ||
           (c >= '0' && c <= '9');
}

/* Write a character to the low domain. */
static void write_low(char c) {
    if (!printable(c)) {
        return;
    }

    /* Again, magic numbers are basically pixel alignments. */
    static unsigned int x = 100 + 2;
    static unsigned int y = 100 + 4 + CHAR_HEIGHT;
    if (y >= 100 + HEIGHT - CHAR_HEIGHT)
        return;
    draw(x, y, c);
    x += CHAR_WIDTH;
    if (x >= 100 + WIDTH - 3) {
        x = 100 + 2;
        y += CHAR_HEIGHT;
    }
}

/* Write a character to the high domain. */
static void write_high(char c) {
    if (!printable(c))
        return;
    static unsigned int x = 200 + WIDTH + 2;
    static unsigned int y = 100 + 4 + CHAR_HEIGHT;
    if (y >= 100 + HEIGHT - CHAR_HEIGHT)
        return;
    draw(x, y, c);
    x += CHAR_WIDTH;
    if (x >= 200 + 2 * WIDTH - 3) {
        x = 200 + WIDTH + 2;
        y += CHAR_HEIGHT;
    }
}

/* Callbacks used below. */
static void out16(uint16_t port, uint16_t value) {
    ports_out16((unsigned int)port, (unsigned int)value);
}

static uint16_t in16(uint16_t port) {
    return (uint16_t)ports_in16((unsigned int)port);
}

/* This function is invoked by the main CAmkES thread in this component. */
int run(void) {
    /* We rely on the CapDL initialiser to map the BGA frame buffer in at this
     * address. This is hard coded here and relies on a patch (included) to the
     * initialiser. This is because CAmkES does not currently support large
     * device regions.
     */
    void *bga_ptr = (void*)0x400000;

    bga = bga_init(bga_ptr, out16, in16);
    bga_set_mode(bga, 1024, 768, 24); /* 1024x768 resolution at 24 BPP */

    ringbuffer_t *low = rb_new((void*)low_input, sizeof(*low_input));
    if (low == NULL) {
        abort();
    }

    ringbuffer_t *high = rb_new((void*)high_input, sizeof(*high_input));
    if (high == NULL) {
        abort();
    }

    borders();

    /* Check both inputs for data and pass it to the relevant framebuffer. */
    while (true) {
        char c;

        if ((c = (char)rb_poll_byte(low)) != 0) {
            write_low(c);
        }

        if ((c = (char)rb_poll_byte(high)) != 0) {
            write_high(c);
        }
    }

    return 0;
}
