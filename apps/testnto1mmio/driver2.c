/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include "driver.h"

void h_handoff(void) {
    uart_put("hello from ");
    uart_put(get_instance_name());
    uart_put_char('\n');
}
