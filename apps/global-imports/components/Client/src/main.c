#include <Client.h>
#include <stdio.h>
#include <vector.h>
#include <shared_int.h>

int run(void) {
    char *str = g_get_string();
    p_print_string(str);
    vector_t vec = g_get_vector();
    p_print_vector(vec);

    printf("%d\n", counter->value);

    return 0;
}
