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

#include <assert.h>
#include <ringbuffer/ringbuffer.h>
#include <stdlib.h>
#include <sys/types.h>

struct ringbuffer {
    volatile unsigned char *base;
    size_t size;
    off_t offset;
};

ringbuffer_t *rb_new(void *base, size_t size) {
    ringbuffer_t *r = malloc(sizeof(*r));
    if (r == NULL) {
        return NULL;
    }

    r->base = (volatile unsigned char*)base;
    r->size = size;
    r->offset = 0;
    return r;
}

void rb_transmit_byte(ringbuffer_t *r, unsigned char c) {
    /* We can't send 0s. */
    if (c == 0) {
        return;
    }

    /* Write 0 into the following slot in the buffer. We always need a zero
     * following the last piece of data to indicate to the receiver where to
     * wait for more data.
     */
    off_t next = (r->offset + 1) % r->size;
    r->base[next] = 0;

    /* Write the character and increment to the next slot for next time. */
    r->base[r->offset] = c;
    r->offset = next;
}

unsigned char rb_poll_byte(ringbuffer_t *r) {
    if (r->base[r->offset] != 0) {

        /* Read the data that's now available and increment to the next slot.
         */
        unsigned char c = r->base[r->offset];
        r->offset = (r->offset + 1) % r->size;

        return c;
    }
    return 0;
}

unsigned char rb_receive_byte(ringbuffer_t *r) {
    unsigned char c;

    /* Busy wait for available data. */
    while ((c = rb_poll_byte(r)) == 0);

    return c;
}

void rb_destroy(ringbuffer_t *r) {
    free(r);
}

size_t rb_transmit_string(ringbuffer_t *r, const char *s) {
    size_t sent = 0;
    while (*s != '\0') {
        rb_transmit_byte(r, (unsigned char)*s);
        sent++;
        s++;
    }
    return sent;
}

size_t rb_receive_string(ringbuffer_t *r, char *s, size_t len) {
    size_t received = 0;
    while (len > 0) {
        *s = (char)rb_receive_byte(r);
        s++;
        len--;
    }
    return received;
}

size_t rb_transmit(ringbuffer_t *r, const void *src, size_t len) {
    size_t sent = 0;
    unsigned char *s = (unsigned char*)src;
    while (len > 0) {
        rb_transmit_byte(r, *s);
        s++;
        len--;
    }
    return sent;
}

size_t rb_receive_data(ringbuffer_t *r, void *dest, size_t len) {
    size_t received = 0;
    unsigned char *d = (unsigned char*)dest;
    while (len > 0) {
        *d = rb_receive_byte(r);
        d++;
        len--;
    }
    return received;
}
