/* @TAG(NICTA_BSD) */

#include <camkes.h>
#include <string.h>
#include <stdio.h>

static size_t uart_write(void *buf, size_t count)
{
	char *data = buf;

	for (size_t i = 0; i < count; ++i) {
		uart_put_char(data[i]);
	}

	return count;
}

int run(void) {
    char c;
    char *str = "This message is sent via UART.\n";


    uart_write(str, strlen(str));

    while (1) {
	c = uart_get_char();
	printf("Input from UART: %c\n", c);

	if (c == 'q') {
		break;
	}
	
    }

    printf("UART client exit...\n");
    return 0;
}
