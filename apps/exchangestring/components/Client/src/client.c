/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <assert.h>
#include <camkes.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int run(void)
{
    char *ret;
    const char *input = "This is a client string.";
    char *output = NULL;
    char *joint = malloc(25);
    strncpy(joint, input, 25);
    joint[24] = '\0';

    ret = a_exchange(input, &output, &joint);

    printf("Client output: %s\n", output);
    printf("Client joint: %s\n", joint);
    printf("Client ret: %s\n", ret);

    free(output);
    free(joint);
    free(ret);
    return 0;
}
