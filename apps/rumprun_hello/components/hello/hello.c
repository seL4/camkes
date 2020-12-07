/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("Hello %s\n", argv[1]);
    printf("sleep 1 sec\n");
    sleep(1);
    printf("sleep 10 sec\n");
    sleep(10);
    printf("finished sleep\n");
}
