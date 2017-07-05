/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <stdlib.h>
#include <string.h>

#define TO_UPPER_DIST ('A' - 'a')

void i_process(const char *arg) {
    char *str = strdup(arg);
    for (char *cptr = str;*cptr != '\0';cptr++) {
        if (*cptr >= 'a' && *cptr <= 'z') {
            *cptr += TO_UPPER_DIST;
        }
    }

    o_process(str);
    free(str);
}
