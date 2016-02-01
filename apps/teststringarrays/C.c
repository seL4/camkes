/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <assert.h>
#include <camkes.h>
#include "heap_check.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *p_foo(void) {
    char *s = strdup("witaj");
    assert(s != NULL);
    printf("%s: Sending %s\n", get_instance_name(), s);
    return s;
}

void p_bar(size_t x_sz, char **x) {
    assert(x != NULL);
    printf("%s: Received x_sz = %u, x = {", get_instance_name(), x_sz);
    for (unsigned int i = 0; i < x_sz; i++) {
        printf("\"%s\", ", x[i]);
    }
    printf("}\n");
}

void p_baz(size_t *x_sz, char ***x) {
    assert(x_sz != NULL);
    assert(x != NULL);
    *x_sz = 2;
    *x = calloc(*x_sz, sizeof(char*));
    assert(*x != NULL);
    (*x)[0] = strdup("alo");
    assert((*x)[0] != NULL);
    (*x)[1] = strdup("mond");
    assert((*x)[1] != NULL);
    printf("%s: Sending *x_sz = %u, *x = {", get_instance_name(), *x_sz);
    for (unsigned int i = 0; i < *x_sz; i++) {
        printf("\"%s\", ", (*x)[i]);
    }
    printf("}\n");
}

void p_qux(size_t *x_sz, char ***x) {
    assert(x_sz != NULL);
    assert(x != NULL);
    printf("%s: Received *x_sz = %u, *x = {", get_instance_name(), *x_sz);
    for (unsigned int i = 0; i < *x_sz; i++) {
        printf("\"%s\", ", (*x)[i]);
        safe_free((*x)[i]);
    }
    printf("}\n");
    safe_free(*x);
    *x_sz = 2;
    *x = calloc(*x_sz, sizeof(char*));
    assert(*x != NULL);
    (*x)[0] = strdup("hola");
    assert((*x)[0] != NULL);
    (*x)[1] = strdup("mundo");
    assert((*x)[1] != NULL);
    printf("%s: Sending *x_sz = %u, *x = {", get_instance_name(), *x_sz);
    for (unsigned int i = 0; i < *x_sz; i++) {
        printf("\"%s\", ", (*x)[i]);
    }
    printf("}\n");
}

void p_quux(size_t x_sz, char **x, size_t *y_sz, char ***y, size_t *z_sz,
        char ***z) {
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
        safe_free((*z)[i]);
    }
    printf("}\n");
    safe_free(*z);
    *y_sz = 2;
    *y = calloc(*y_sz, sizeof(char*));
    assert(*y != NULL);
    (*y)[0] = strdup("ola");
    assert((*y)[0] != NULL);
    (*y)[1] = strdup("mundo");
    assert((*y)[1] != NULL);
    *z_sz = 2;
    *z = calloc(*z_sz, sizeof(char*));
    (*z)[0] = strdup("hallo");
    assert((*z)[0] != NULL);
    (*z)[1] = strdup("welt");
    assert((*z)[1] != NULL);
    printf("%s: Sending *y_sz = %u, *y = {", get_instance_name(), *y_sz);
    for (unsigned int i = 0; i < *y_sz; i++) {
        printf("\"%s\", ", (*y)[i]);
    }
    printf("}, *z_sz = %u, *z = {", *z_sz);
    for (unsigned int i = 0; i < *z_sz; i++) {
        printf("\"%s\", ", (*z)[i]);
    }
    printf("}\n");
}

void p_corge(const size_t *x_sz, char ***x) {
    assert(x_sz != NULL);
    assert(x != NULL);
    printf("%s: Received *x_sz = %u, *x = {", get_instance_name(), *x_sz);
    for (unsigned int i = 0; i < *x_sz; i++) {
        printf("\"%s\", ", (*x)[i]);
    }
    printf("}\n");
}
