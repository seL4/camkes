/* @TAG(DATA61_BSD) */

#include <camkes.h>

int p1_increment(int x) {
    int y = p2_increment(x);
    return y + 1;
}
