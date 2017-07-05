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

#include <assert.h>
#include <camkes.h>
#include "heap_check.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run(void) {

#ifdef NDEBUG
    printf("WARNING: ASSERTIONS DISABLED; NOTHING WILL BE TESTED\n");
#endif

    const char *name = get_instance_name();

    printf("%s: Calling p_foo()...\n", name);
    char *s = p_foo();
    printf("%s: Received \"%s\"\n", name, s);

    printf("\n");

    const char *s1[] = {"hello", "world"};
    size_t s1_sz = sizeof(s1) / sizeof(s1[0]);
    printf("%s: Calling p_bar(%u, {\"%s\", \"%s\"})...\n", name, s1_sz, s1[0],
        s1[1]);
    p_bar(s1_sz, s1);

    printf("\n");

    char **s2 = NULL;
    size_t s2_sz;
    printf("%s: Calling p_baz(&s2_sz, &s2)...\n", name);
    p_baz(&s2_sz, &s2);
    assert(s2 != NULL);
    printf("%s: Received s2_sz = %u, s2 = {", name, s2_sz);
    for (unsigned int i = 0; i < s2_sz; i++) {
        printf("\"%s\", ", s2[i]);
        safe_free(s2[i]);
    }
    printf("}\n");
    safe_free(s2);

    printf("\n");

    size_t s3_sz = 2;
    char **s3 = calloc(s2_sz, sizeof(char*));
    assert(s3 != NULL);
    s3[0] = strdup("ciao");
    assert(s3[0] != NULL);
    s3[1] = strdup("mondo");
    assert(s3[1] != NULL);
    printf("%s: s3_sz = %u, s3 = {", name, s3_sz);
    for (unsigned int i = 0; i < s3_sz; i++) {
        printf("\"%s\", ", s3[i]);
    }
    printf("}\n");
    printf("%s: Calling p_qux(&s3_sz, &s3)...\n", name);
    p_qux(&s3_sz, &s3);
    assert(s3 != NULL);
    printf("%s: Received s3_sz = %u, s3 = {", name, s3_sz);
    for (unsigned int i = 0; i < s3_sz; i++) {
        printf("\"%s\", ", s3[i]);
        safe_free(s3[i]);
    }
    printf("}\n");
    safe_free(s3);

    printf("\n");

    const char *s4[] = { "bonjour", "le", "monde" };
    size_t s4_sz = sizeof(s4) / sizeof(s4[0]);
    char **s5 = NULL;
    size_t s5_sz;
    size_t s6_sz = 2;
    char **s6 = calloc(s6_sz, sizeof(char*));
    assert(s6 != NULL);
    s6[0] = strdup("ahoj");
    assert(s6[0] != NULL);
    s6[1] = strdup("svete");
    assert(s6[1] != NULL);
    printf("%s: s6_sz = %u, s6 = {", name, s6_sz);
    for (unsigned int i = 0; i < s6_sz; i++) {
        printf("\"%s\", ", s6[i]);
    }
    printf("}\n");
    printf("%s: Calling p_quux(%u, {\"%s\", \"%s\", \"%s\"}, &s5_sz, &s5, "
        "&s6_sz, &s6)...\n", name, s4_sz, s4[0], s4[1], s4[2]);
    p_quux(s4_sz, s4, &s5_sz, &s5, &s6_sz, &s6);
    assert(s5 != NULL);
    printf("%s: Received s5_sz = %u, s5 = {", name, s5_sz);
    for (unsigned int i = 0; i < s5_sz; i++) {
        printf("\"%s\", ", s5[i]);
        safe_free(s5[i]);
    }
    printf("}, s6_sz = %u, s6 = {", s6_sz);
    for (unsigned int i = 0; i < s6_sz; i++) {
        printf("\"%s\", ", s6[i]);
        safe_free(s6[i]);
    }
    printf("}\n");

    printf("\n");

    /* This last case makes no real sense, but we still test that it works. */
    size_t s7_sz = 2;
    char ***s7 = malloc(sizeof(char**));
    assert(s7 != NULL);
    *s7 = malloc(s7_sz * sizeof(char*));
    assert(*s7 != NULL);
    (*s7)[0] = strdup("konnichiwa");
    assert((*s7)[0] != NULL);
    (*s7)[1] = strdup("sekai");
    assert((*s7)[1] != NULL);
    printf("%s: Calling p_corge(%u, {\"%s\", \"%s\"})...\n", name, s7_sz,
        (*s7)[0], (*s7)[1]);
    p_corge(&s7_sz, s7);
    safe_free((*s7)[0]);
    safe_free((*s7)[1]);
    safe_free(*s7);
    safe_free(s7);

    printf("\n");

    printf("All OK\n");
    return 0;
}
