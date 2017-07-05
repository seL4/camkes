/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <string.h>

void l__init(void) {
}

static struct {
    const char *key;
    const char *value;
} dict[] = {
    {
        .key = "foo",
        .value = "bar",
    },
    {
        .key = "secret",
        .value = "baz",
    }
};

/* Lookup and return the value associated with 'key' */
char *l_get_value(const char *key) {
    for (unsigned int i = 0; i < sizeof(dict) / sizeof(dict[0]); ++i) {
        if (!strcmp(key, dict[i].key)) {
            return strdup(dict[i].value);
        }
    }
    /* Not found */
    return strdup("");
}
