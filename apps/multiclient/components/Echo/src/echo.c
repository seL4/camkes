/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

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
