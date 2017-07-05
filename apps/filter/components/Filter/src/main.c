/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <string.h>

void external__init(void) {}

char *external_get_value(const char *key) {
    if (!strcmp(key, "secret")) {
        /* Block reading the value of "secret" */
        return strdup("");
    } else {
        /* Allow anything else */
        return backing_get_value(key);
    }
}
