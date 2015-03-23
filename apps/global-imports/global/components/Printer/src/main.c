#include <Printer.h>
#include <stdio.h>
#include <vec.h>

void printer_print_string(char *str) {
    printf("%s", str);
}
void printer_print_vec(vec_t v) {
    printf("(%2f, %2f)\n", v.x, v.y);
}
