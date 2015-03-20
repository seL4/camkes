#include <Client.h>
#include <stdio.h>
#include <vec.h>
#include <shared_int.h>

int run(void) {
    char *str = g_get_string();
    p_print_string(str);
    vec_t vec = g_get_vec();
    p_print_vec(vec);

    printf("%d\n", counter->value);

    return 0;
}
