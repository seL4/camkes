/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <Printer.h>
#include <stdio.h>
#include <vec.h>

void printer_print_string(const char *str) {
    printf("%s", str);
}
void printer_print_vec(vec_t v) {
    printf("(%2f, %2f)\n", v.x, v.y);
}
