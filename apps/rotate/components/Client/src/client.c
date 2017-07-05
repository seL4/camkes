/* @TAG(NICTA_BSD) */

#include <camkes.h>
#include <stdio.h>

int run(void) {
    MyType_t a, b, c, d;

    a.i = 1;
    b.i = 2;
    c.i = 3;
    d.i = 4;

    printf("Beforehand we have (ret)%d, (in)%d, (out)%d, (inout)%d\n", a.i, b.i, c.i, d.i);
    a = p_rotate(b, &c, &d);
    printf("Afterwards we have (ret)%d, (in)%d, (out)%d, (inout)%d\n", a.i, b.i, c.i, d.i);
    return 0;
}
