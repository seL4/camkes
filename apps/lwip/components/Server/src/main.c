#include <camkes.h>
#include <autoconf.h>
#include <stdio.h>
/* remove the camkes ERR_IF definition to not overlap with lwip */
#undef ERR_IF

#include <ethdrivers/lwip.h>
#include <lwip/timers.h>

#define LWIP_TICK_MS 100

static uint32_t counter_s = 0;

void eth_init();
void interface_tick();

u32_t sys_now(void) {
    return counter_s/10;
}


void pre_init(void)
{
    eth_init();
    /* Start the timer for the TCP stack */
    timer_periodic(0, NS_IN_MS * LWIP_TICK_MS);
}
/* Callback that gets called when the timer fires. */
void timer_complete_callback(void)
{
    int err = mut_lock();
    counter_s +=1;
    sys_check_timeouts();
    interface_tick();
    err = mut_unlock();
}


int run(void)
{
    int retval = 0;
    return retval;
}