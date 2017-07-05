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

#include <stdio.h>
#include <camkes.h>

#define TO_ECHO 42

int run(void) {

    printf("Echoing: %d == %d\n", TO_ECHO, echo_echo(TO_ECHO));

    return 0;
}
