/*
 * Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>

int run()
{
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
