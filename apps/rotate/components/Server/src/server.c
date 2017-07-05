/* @TAG(DATA61_BSD) */

#include <camkes.h>

MyType_t s_rotate(MyType_t a, MyType_t *b, MyType_t *c) {
    b->i = c->i;
    c->i = a.i;
    return a;
}
