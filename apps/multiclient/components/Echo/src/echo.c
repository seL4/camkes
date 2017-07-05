/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <string.h>

int count = 0;
inline void udelay(uint32_t us){
	volatile int i;
	for(; us > 0; us--)
		for(i = 0; i < 100; i++);
}

void s__init(void) {
}

int s_echo_int(void) {
    const char *str = "This string is in the dataport.";

    udelay(100000);
    strcpy((char*)d, str);
    e_emit();
    return count++;
}
