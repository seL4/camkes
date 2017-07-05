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

/* This interface allows a user to treat a region of memory as a ring buffer,
 * to which they read or write. It is intended for unidirectional communication
 * only.
 *
 * Note that, although it is not obvious from this interface, there is no flow
 * control provided. The effect of this is that a sender transmitting
 * characters at a rapid rate can have an entire buffer's worth of their data
 * missed by the receiver. This is semi-deliberate because any mechanism to
 * prevent this would introduce a back channel from the receiver to the sender.
 */

#ifndef _RINGBUFFER_RINGBUFFER_H_
#define _RINGBUFFER_RINGBUFFER_H_

#include <sys/types.h>

/* Opaque type. Callers should be agnostic to the contents of this struct. */
typedef struct ringbuffer ringbuffer_t;

/* Create a new ring buffer.
 *  base - A pointer to the start of the region to use as the buffer.
 *  size - The size of the buffer in bytes.
 * Returns NULL on failure.
 */
ringbuffer_t *rb_new(void *base, size_t size);

/* Send a byte.
 *  r - Buffer to send via.
 *  c - Byte to send.
 */
void rb_transmit_byte(ringbuffer_t *r, unsigned char c);

/* Receive a byte.
 *  r - Buffer to read from.
 * Returns the character received. Does not return until it has received some
 * data.
 */
unsigned char rb_receive_byte(ringbuffer_t *r);

/* Poll for new data. Identical to rb_receive_byte, except it is non-blocking
 * and returns 0 to indicate no data available.
 */
unsigned char rb_poll_byte(ringbuffer_t *r);

/* Destroy a ring buffer and deallocate associated resources. */
void rb_destroy(ringbuffer_t *r);

/* Higher-level wrappers. */

/* Send a null-terminated string.
 *  r - Buffer to send via.
 *  s - String to send.
 & Returns the number of characters sent.
 */
size_t rb_transmit_string(ringbuffer_t *r, const char *s);

/* Receive a string. Note, this function does not null-terminate the resulting
 * string.
 *  r - Buffer to read from.
 *  s - Location to receive into.
 *  len - Maximum characters to write into the destination location.
 * Returns the number of characters written into the destination location.
 */
size_t rb_receive_string(ringbuffer_t *r, char *s, size_t len);

/* Send an arbitrary block of data. The block cannot contain any 0 bytes.
 *  r - Buffer to send via.
 *  src - Location to read from.
 *  len - Number of bytes to send.
 * Returns the number of bytes sent.
 */
size_t rb_transmit(ringbuffer_t *r, const void *src, size_t len);

/* Receive an arbitrary block of data.
 *  r - Buffer to read from.
 *  dest - Location to write bytes received into.
 *  len - Maximum number of bytes to write to destination location.
 * Returns the number of bytes received.
 */
size_t rb_receive(ringbuffer_t *r, void *dest, size_t len);

#endif
