/*
 * Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <assert.h>
#include <camkes.h>

// FFI function called from CakeML to send output over IPC to the Consumer
void ffiemit_string(unsigned char *c, long clen, unsigned char *a, long alen)
{
    server_transfer_string(c);
}
