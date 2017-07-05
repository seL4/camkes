/* @TAG(DATA61_BSD) */

#include <camkes.h>

int incoming_echo(int x) {
    return outgoing_echo(x);
}
