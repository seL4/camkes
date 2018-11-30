/*
 * Copyright 2018, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#include <camkes.h>

int run() {
    while (true) {
        server_transfer_string("This will get through 1\n");
        server_transfer_string("Won't get through 1\n");
        server_transfer_string("Won't get through 2\n");
        server_transfer_string("This will get through 2\n");
        server_transfer_string("This will get through 3\n");
        server_transfer_string("Also won't get through\n");
        server_transfer_string("Malformed message\n");
        server_transfer_string("Yeeeha\n");
    }
}
