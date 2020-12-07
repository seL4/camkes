/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>
#include <configuration.h>
#include <terminal_terminal.h>

#define ESC ((char)27)

#define RESET_ATTRIBUTES "\033[0m"

static void write_char(int x, int y, char c)
{
    /* Control sequence to jump to a terminal position and write. Note, the
     * first character in a row is at index 1, not 0.
     */
    printf("%c[%d;%dH%c", ESC, y, x + 1, c);
}

/* Draw a border around a region. */
static void borderise(int x, int y, int width, int height, const char *colour)
{
    int i, j;
    printf("%s", colour);

    i = x - 1;
    j = y - 1;
    if (i >= 0 && j >= 0 && i <= TERMINAL_WIDTH && j <= TERMINAL_HEIGHT) {
        write_char(i, j, '+');
    }

    i = x + width;
    j = y - 1;
    if (i >= 0 && j >= 0 && i <= TERMINAL_WIDTH && j <= TERMINAL_HEIGHT) {
        write_char(i, j, '+');
    }

    i = x - 1;
    j = y + height;
    if (i >= 0 && j >= 0 && i <= TERMINAL_WIDTH && j <= TERMINAL_HEIGHT) {
        write_char(i, j, '+');
    }

    i = x + width;
    j = y + height;
    if (i >= 0 && j >= 0 && i <= TERMINAL_WIDTH && j <= TERMINAL_HEIGHT) {
        write_char(i, j, '+');
    }

    j = y - 1;
    for (i = x; i < x + width; ++i) {
        if (i >= 0 && j >= 0 && i <= TERMINAL_WIDTH && j <= TERMINAL_HEIGHT) {
            write_char(i, j, '-');
        }
    }

    i = x - 1;
    for (j = y; j < y + height; ++j) {
        if (i >= 0 && j >= 0 && i <= TERMINAL_WIDTH && j <= TERMINAL_HEIGHT) {
            write_char(i, j, '|');
        }
    }

    j = y + height;
    for (i = x; i < x + width; ++i) {
        if (i >= 0 && j >= 0 && i <= TERMINAL_WIDTH && j <= TERMINAL_HEIGHT) {
            write_char(i, j, '-');
        }
    }

    i = x + width;
    for (j = y; j < y + height; ++j) {
        if (i >= 0 && j >= 0 && i <= TERMINAL_WIDTH && j <= TERMINAL_HEIGHT) {
            write_char(i, j, '|');
        }
    }
    printf("%s", RESET_ATTRIBUTES);
}

void domain1__init(void)
{
    /* Blank the terminal. */
    for (int i = 0; i < TERMINAL_WIDTH; ++i) {
        for (int j = 0; j < TERMINAL_HEIGHT; ++j) {
            write_char(i, j, ' ');
        }
    }
}

int domain1_put_char(int x, int y, char data)
{
    static int border = 0;
    if (!border) {
        borderise(DOMAIN1_X, DOMAIN1_Y, DOMAIN1_WIDTH, DOMAIN1_HEIGHT, DOMAIN1_COLOUR);
        border = 1;
    }
    if (data == ESC) {
        /* Prevent clients sending control sequences. */
        return -1;
    }
    /* Check if the coordinates are out of bounds. */
    if (x < 0 || y < 0 || x >= DOMAIN1_WIDTH || y >= DOMAIN1_HEIGHT ||
        x + DOMAIN1_X >= TERMINAL_WIDTH ||
        y + DOMAIN1_HEIGHT >= TERMINAL_HEIGHT) {
        return -1;
    }
    printf("%s", DOMAIN1_COLOUR);
    write_char(DOMAIN1_X + x, DOMAIN1_Y + y, data);
    printf("%s", RESET_ATTRIBUTES);
    return 0;
}

void domain2__init(void)
{
    /* No need to blank the terminal here, as it is done in the other init. */
}

int domain2_put_char(int x, int y, char data)
{
    static int border = 0;
    if (!border) {
        borderise(DOMAIN2_X, DOMAIN2_Y, DOMAIN2_WIDTH, DOMAIN2_HEIGHT, DOMAIN2_COLOUR);
        border = 1;
    }
    if (data == ESC) {
        /* Prevent clients sending control sequences. */
        return -1;
    }
    /* Check if the coordinates are out of bounds. */
    if (x < 0 || y < 0 || x >= DOMAIN2_WIDTH || y >= DOMAIN2_HEIGHT ||
        x + DOMAIN2_X >= TERMINAL_WIDTH ||
        y + DOMAIN2_HEIGHT >= TERMINAL_HEIGHT) {
        return -1;
    }
    printf("%s", DOMAIN2_COLOUR);
    write_char(DOMAIN2_X + x, DOMAIN2_Y + y, data);
    printf("%s", RESET_ATTRIBUTES);
    return 0;
}
