/* @TAG(NICTA_BSD) */

#ifndef _LIBGA_BGA_H_
#define _LIBGA_BGA_H_

#include <stdint.h>

/* More information about the BGA device itself is available from
 * http://wiki.osdev.org/Bochs_VBE_Extensions.
 */

/* Opaque pointer as a handle to the device. */
typedef struct bga *bga_p;

/* Initialise the driver. Returns NULL on failure.
 *  framebuffer - A pointer to the device frame mapped into your address space.
 *  ioport_write - Callback for writing to an IO port.
 *  ioport_read - Callback for reading from an IO port.
 */
bga_p bga_init(void *framebuffer,
    void (*ioport_write)(uint16_t port, uint16_t value),
    uint16_t (*ioport_read)(uint16_t port));

/* Destroy and clean up resources associated with an initialised device.
 * Returns 0 on success, non-zero on failure.
 */
int bga_destroy(bga_p device);

/* Get the version number of this device. */
uint16_t bga_version(bga_p device);

/* Set the mode of the device. Returns 0 on success. On error, the device might
 * be left in an invalid state.
 *  width - The width of the display in pixels.
 *  height - The height of the display in pixels.
 *  bpp - The bits per pixel.
 */
int bga_set_mode(bga_p device, unsigned int width, unsigned int height,
    unsigned int bpp);

/* Set the value of the pixel at (x, y). How value is interpreted is dependent
 * on the current bits per pixel configuration. To know how to pass this value
 * correctly, consult http://wiki.osdev.org/Bochs_VBE_Extensions. Returns 0 on
 * success.
 *
 * This function is mainly for drawing simple output to the screen. For
 * anything performance-critical you will want to use the raw frame buffer
 * access below.
 *
 * XXX: This function has not been tested with BPPs other than 24.
 */
int bga_set_pixel(bga_p device, unsigned int x, unsigned int y, char *value);

/* Get a pointer to the frame buffer. You can output to the screen by directly
 * writing into this buffer. To do this correctly you will have to consult the
 * Bochs documentation for formatting details.
 */
void *bga_get_framebuffer(bga_p device);

#endif /* !_LIBBGA_BGA_H_ */
