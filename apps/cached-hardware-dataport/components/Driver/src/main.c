/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <camkes.h>
#include <camkes/io.h>

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <platsupport/io.h>
#include <platsupport/chardev.h>
#include <platsupport/plat/serial.h>

/* WARNING!
 * This program is a regression test for CAmkES and should NOT be used as
 * a reference for writing software. Caching memory-mapped registers is
 * dangerous as when a cache line is written back to memory, all the addresses
 * in the line are written. If these are the addresses of memory-mapped
 * registers, writing to them can cause unexpected hardware behaviour.
 */

int run(void) {

    ps_io_ops_t io_ops;
    int error;

    error = camkes_io_ops(&io_ops);
    assert(error == 0);

    printf("Initializing uart...\n");
    ps_chardevice_t uart;
    ps_chardevice_t *uart_ptr = ps_cdev_init(PS_SERIAL_DEFAULT, &io_ops, &uart);
    assert(uart_ptr == &uart);

    printf("Sending message \"Hello, World!\\n\" over uart...\n");
    /* Write a message to the uart */
    char *message = "Hello, World!\n";
    ps_cdev_write(&uart, message, strlen(message), NULL, NULL);

    printf("Flushing uart from the cache...\n");
    /* Flush the dataport from the cache */
    error = registers_flush_cache(0, 0x1000);
    assert(error == 0);

    printf("Flushing an invalid range. Should produce an error message...\n");
    /* Test that flushing an invalid range is an error */
    error = registers_flush_cache(0, 0x2000); // the dataport xs 0x1000 bytes
    assert(error != 0);

    /* Don't use the cached uart for the final message, as it won't necessarily
     * print all the characters.
     */
    printf("All is well in the universe\n");
    return 0;
}
