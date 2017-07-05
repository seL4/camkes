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

#include <camkes.h>
#include <stdlib.h>
#include <string.h>

void i_process(const char *arg) {
    char *str = strdup(arg);
    int last_idx = strlen(str)-1;
    for (int i = 0;i<last_idx/2;i++) {
        char tmp = str[i];
        str[i] = str[last_idx-i];
        str[last_idx-i] = tmp;
    }

    o_process(str);
    free(str);
}
