/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <assert.h>
#include <camkes.h>
#include <stdio.h>
#include <stdlib.h>

char *q_foo(void)
{
    char *s = p_foo();
    printf("%s: Received \"%s\"\n", get_instance_name(), s);
    return s;
}

void q_bar(size_t x_sz, char **x)
{
    printf("%s: Received x_sz = %u, x = {", get_instance_name(), x_sz);
    for (unsigned int i = 0; i < x_sz; i++) {
        printf("\"%s\", ", x[i]);
    }
    printf("}\n");
    p_bar(x_sz, x);
}

void q_baz(size_t *x_sz, char ***x)
{
    assert(x_sz != NULL);
    assert(x != NULL);
    p_baz(x_sz, x);
    printf("%s: Received *x_sz = %u, *x = {", get_instance_name(), *x_sz);
    for (unsigned int i = 0; i < *x_sz; i++) {
        printf("\"%s\", ", (*x)[i]);
    }
    printf("}\n");
}

void q_qux(size_t *x_sz, char ***x)
{
    assert(x_sz != NULL);
    assert(x != NULL);
    printf("%s: Received *x_sz = %u, *x = {", get_instance_name(), *x_sz);
    for (unsigned int i = 0; i < *x_sz; i++) {
        printf("\"%s\", ", (*x)[i]);
    }
    printf("}\n");
    p_qux(x_sz, x);
    printf("%s: Received *x_sz = %u, *x = {", get_instance_name(), *x_sz);
    for (unsigned int i = 0; i < *x_sz; i++) {
        printf("\"%s\", ", (*x)[i]);
    }
    printf("}\n");
}

void q_quux(size_t x_sz, char **x, size_t *y_sz, char ***y, size_t *z_sz,
            char ***z)
{
    assert(x != NULL);
    assert(y_sz != NULL);
    assert(y != NULL);
    assert(z_sz != NULL);
    assert(z != NULL);
    printf("%s: Received x_sz = %u, x = {", get_instance_name(), x_sz);
    for (unsigned int i = 0; i < x_sz; i++) {
        printf("\"%s\", ", x[i]);
    }
    printf("}, *z_sz = %u, *z = {", *z_sz);
    for (unsigned int i = 0; i < *z_sz; i++) {
        printf("\"%s\", ", (*z)[i]);
    }
    printf("}\n");
    p_quux(x_sz, x, y_sz, y, z_sz, z);
    printf("%s: Received *y_sz = %u, *y = {", get_instance_name(), *y_sz);
    for (unsigned int i = 0; i < *y_sz; i++) {
        printf("\"%s\", ", (*y)[i]);
    }
    printf("}, *z_sz = %u, *z = {", *z_sz);
    for (unsigned int i = 0; i < *z_sz; i++) {
        printf("\"%s\", ", (*z)[i]);
    }
    printf("}\n");
}

void q_corge(const size_t *x_sz, char ***x)
{
    assert(x_sz != NULL);
    assert(x != NULL);
    printf("%s: Received *x_sz = %u, *x = {", get_instance_name(), *x_sz);
    for (unsigned int i = 0; i < *x_sz; i++) {
        printf("\"%s\", ", (*x)[i]);
    }
    printf("}\n");
    p_corge(x_sz, x);
}
