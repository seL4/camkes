#include <Printer.h>
#include <stdio.h>
#include <vector.h>

void printer_print_string(char *str) {
    printf("%s", str);
}
void printer_print_vector(vector_t v) {
    printf("(%2f, %2f)\n", v.x, v.y);
}
