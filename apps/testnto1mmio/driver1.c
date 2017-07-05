/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include "driver.h"

int run(void) {
    uart_put("hello from ");
    uart_put(get_instance_name());
    uart_put_char('\n');
    h_handoff();
    return 0;
}
