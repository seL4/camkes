/* @TAG(DATA61_BSD) */

#include <camkes.h>

static unsigned int counter;

unsigned int
ss_swap(int *a, int *b){
    int temp = *a;
    *a = *b; *b = temp;
    counter++;
    return counter;
}
