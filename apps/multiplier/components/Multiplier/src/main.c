/* @TAG(NICTA_BSD) */

#include <assert.h>
#include <camkes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int a_calculate(size_t operands_sz, const int *operands, size_t *other_sz, int **other, size_t *inplace_sz, int **inplace) {
    const char *name = get_instance_name();
    int total = 1;
    for (int i = 0; i < operands_sz; i++) {
        printf("%s: multiplying %d\n", name, operands[i]);
        total *= operands[i];
    }
    int i;
    *other = (int*)malloc(sizeof(int) * *inplace_sz);
    assert(*other != NULL);
    for (i = 0; i < *inplace_sz; i++) {
        printf("%s: stashing %d\n", name, (*inplace)[i]);
        (*other)[i] = (*inplace)[i];
    }
    *other_sz = i;
    for (i = 1; i < *inplace_sz; i++) {
        printf("%s: multiplying %d\n", name, (*inplace)[i]);
        (*inplace)[0] *= (*inplace)[i];
    }
    *inplace_sz = 1;
    return total;
}
