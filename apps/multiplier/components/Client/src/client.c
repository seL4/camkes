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

int run(void)
{
    int operands[] = { 342, 74, 283, };
    int *inplace;
    int *other;
    size_t operands_sz = sizeof(operands) / sizeof(int);
    size_t other_sz;
    size_t inplace_sz = 2;
    const char *name = get_instance_name();

    inplace = (int *)malloc(sizeof(int) * inplace_sz);
    assert(inplace != NULL);
    inplace[0] = 7;
    inplace[1] = 8;

    printf("%s: what's the answer to ", name);
    for (int i = 0; i < operands_sz; i++) {
        printf("%d ", operands[i]);
        if (i != operands_sz - 1) {
            printf("* ");
        }
    }
    printf("\n");
    printf("%s: and ", name);
    for (int i = 0; i < inplace_sz; i++) {
        printf("%d ", inplace[i]);
        if (i != inplace_sz - 1) {
            printf("* ");
        }
    }
    printf("\n");

    int answer = a_calculate(operands_sz, operands, &other_sz, &other, &inplace_sz, &inplace);

    printf("%s: first result was %d\n", name, answer);
    printf("%s: second result was %d (len that should have been 1 was %d)\n", name, inplace[0], inplace_sz);
    printf("%s: other is {", name);
    for (int i = 0; i < other_sz; i++) {
        printf("%d, ", other[i]);
    }
    printf("}\n");
    return 0;
}
