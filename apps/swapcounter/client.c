/* @TAG(NICTA_BSD) */

#include <camkes.h>

int run(void) {
    int x = 3;
    int y = 5;
    unsigned int i;
    i = cs_swap(&x, &y);
    /* Printf for tests,
     * you should probably remove this line if wanting to run proofs */
    printf("done\n");
    return 0;
}
