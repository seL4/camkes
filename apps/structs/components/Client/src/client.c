/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <stdio.h>

int run(void)
{

    printf("struct: %s: height plus age is %d\n", config.name, config.age + config.height);
    printf("inline_struct: %d: height plus age is %d\n", inline_struct.age, inline_struct.height);
    printf("nested_struct: %d: height \n", nested_struct.c.a);
    printf("array_struct: contains %zd items, first one is %d\n", sizeof(array_struct) / sizeof(array_struct[0]), array_struct[0].a);
    printf("numbers: contains %zd items, first one is %d\n", sizeof(numbers) / sizeof(numbers[0]), numbers[0]);
    printf("strings: contains %zd items, first one is \"%s\"\n", sizeof(strings) / sizeof(strings[0]), strings[0]);
    printf("array_in_struct: array length: %zd, first element %d\n", sizeof(array_in_struct.b) / sizeof(array_in_struct.b[0]), array_in_struct.b[0]);
    return 0;
}
