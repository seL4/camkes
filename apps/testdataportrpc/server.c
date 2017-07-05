/* @TAG(DATA61_BSD) */

#include <assert.h>
#include <camkes.h>
#include <stddef.h>
#include <string.h>

static char *echo(const char *s) {
    char *p = strdup(s);
    assert(p != NULL);
    return p;
}

char *b_echo(const char *s) {
    return echo(s);
}

char *d_echo(const char *s) {
    return echo(s);
}

char *f_echo(const char *s) {
    return echo(s);
}

char *h_echo(const char *s) {
    return echo(s);
}

char *j_echo(const char *s) {
    return echo(s);
}
