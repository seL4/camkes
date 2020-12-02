/*
 * Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <string.h>
#include <sel4/sel4.h>
#include <utils/util.h>

#define FFI_SUCCESS 0
#define FFI_FAILURE 1

seL4_CPtr virtqueue_wait_notification(void);

// Return the global endpoint for our CakeML filter component
void ffiget_global_endpoint(char * c, unsigned long clen, char * a, unsigned long alen) {
    assert(alen >= 1 + sizeof(seL4_CPtr));
    seL4_CPtr src = virtqueue_wait_notification();
    memcpy(a + 1, &src, sizeof(seL4_CPtr));
    a[0] = FFI_SUCCESS;
}
