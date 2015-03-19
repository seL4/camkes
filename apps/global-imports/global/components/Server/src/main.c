#include <Server.h>
#include <string.h>
#include <vector.h>

void getter__init(void) {
    counter->value = 0;
}

char * getter_get_string(void) {
    counter->value++;
    return strdup("Hello, World!\n");
}

vector_t getter_get_vector(void) {
    counter->value++;
    return (vector_t) {.x = 4.0, .y = 2.0};
}
