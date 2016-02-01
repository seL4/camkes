/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

/* The code in this file was partially extracted from David Pollack's summer
 * project.
 */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <bga/bga.h>

struct bga {
    void *framebuffer;

    /* IO port functions. */
    uint16_t (*read)(uint16_t port);
    void (*write)(uint16_t port, uint16_t value);

    /* Current configuration. */
    unsigned int width;
    unsigned int height;
    unsigned int bpp;
};

/* The BGA device is controlled by operating on two IO ports, first the index
 * port to indicate what register you are trying to read/write and then the
 * data port to read or write the actual register.
 */
static const uint16_t INDEX = 0x1ce;
static const uint16_t DATA  = 0x1cf;
static void write_data(bga_p device, uint16_t index, uint16_t data) {
    assert(device != NULL);
    device->write(INDEX, index);
    device->write(DATA, data);
}
static uint16_t read_data(bga_p device, uint16_t index) {
    assert(device != NULL);
    device->write(INDEX, index);
    return device->read(DATA);
}

/* After writing INDEX_ENABLED to the index port, you can write either 0x0000
 * or 0x0001 to the data port to disable or enable the device respectively.
 */
static const uint16_t INDEX_ENABLED = 0x0004;
static void disable(bga_p device) {
    const uint16_t data_disable = 0x0000;
    write_data(device, INDEX_ENABLED, data_disable);
}
static void enable(bga_p device) {
    /* Note that we unconditionally use a linear frame buffer and clear the
    * screen. Not ideal, but the emphasis is on simplicity in this driver.
    */
    const uint16_t data_enable = 0x0001;
    const uint16_t lfb = 0x0040;
    write_data(device, INDEX_ENABLED, data_enable | lfb);
}

uint16_t bga_version(bga_p device) {
    assert(device != NULL);
    const uint16_t index_id = 0x0000; /* Index to read version information. */
    const uint16_t mask = (uint16_t)~0xb0c0;
    uint16_t result = read_data(device, index_id);
    return result & mask;
}

bga_p bga_init(void *framebuffer,
        void (*ioport_write)(uint16_t port, uint16_t value),
        uint16_t (*ioport_read)(uint16_t port)) {
    bga_p device = (bga_p)malloc(sizeof(struct bga));
    if (device == NULL) {
        return device;
    }

    memset(device, 0, sizeof(*device));
    device->framebuffer = framebuffer;
    device->write = ioport_write;
    device->read = ioport_read;

    return device;
}

int bga_destroy(bga_p device) {
    free(device);
    return 0;
}

int bga_set_mode(bga_p device, unsigned int width, unsigned int height, unsigned int bpp) {
    /* We need to disable the device to change these parameters. */
    disable(device);

    /* Relevant indicies to write to. */
    const uint16_t x_resolution = 0x0001;
    const uint16_t y_resolution = 0x0002;
    const uint16_t bits_per_pixel = 0x0003;

    /* Setup the requested settings. */
    write_data(device, x_resolution, width);
    device->width = width;
    write_data(device, y_resolution, height);
    device->height = height;
    write_data(device, bits_per_pixel, bpp);
    device->bpp = bpp;

    /* Finally re-enable the device to have the settings take effect. */
    enable(device);

    return 0;
}

int bga_set_pixel(bga_p device, unsigned int x, unsigned int y, char *value) {
    char *target;
    unsigned int coord_factor;
    size_t len;

    /* XXX: None of these other than 24-bit have been tested and they are most
     * likely incorrect.
     */

    switch (device->bpp) {
        case 8: {
            coord_factor = 1;
            len = 1;
            break;
        } case 15:
          case 16: {
            coord_factor = 2;
            len = 2;
            break;
        } case 24: {
            coord_factor = 3;
            len = 3;
            break;
        } case 32: {
            coord_factor = 4;
            len = 3;
            break;
        } default: {
            /* Unsupported BPP. */
            return -1;
        }
    }

    /* Determine where we need to write and copy the pixel data over. */
    target = ((char*)device->framebuffer) + (y * device->width + x) * coord_factor;
    (void)memcpy(target, value, len);

    return 0;
}

void *bga_get_framebuffer(bga_p device) {
    return device->framebuffer;
}
