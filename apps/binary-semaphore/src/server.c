/*
 * Copyright 2016, Data 61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <camkes.h>

static int global;

static void callback(void *arg) {
    int *ret = arg;
    *ret = global;
    int error = binsem_post();
    assert(!error);
}

int echo_echo(int i) {
    int ret;
    global = i;
    int error = ready_reg_callback(callback, &ret);
    assert(!error);
    error = binsem_wait();
    assert(!error);
    return ret;
}
