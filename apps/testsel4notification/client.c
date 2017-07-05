/* @TAG(DATA61_BSD) */

#include <assert.h>
#include <camkes.h>
#include <stdio.h>
#include <utils/util.h>

int run(void) {
#ifdef NDEBUG
    printf("WARNING: assertions disabled! Nothing will be tested.\n");
#endif

    /* Without any event having been sent, poll should fail. */
    int result UNUSED = e_poll();
    assert(result == 0);

    /* Spin for a while to let various glue code reach a quiescent state. */
    for (unsigned int i = 0; i < 100000; i++) {
        asm volatile ("");
    }

    /* There should still be no pending event, even if we check repeatedly. */
    for (unsigned int i = 0; i < 10; i++) {
        result = e_poll();
        assert(result == 0);
    }

    /* Now let's cause an event to be emitted. */
    n_notify_me();

    /* Poll should now be successful. */
    result = e_poll();
    assert(result == 1);

    /* Polling again should find no event. */
    result = e_poll();
    assert(result == 0);

    /* Doing the same with two pending events should yield either 1 or 2
     * pending events, depending on whether the connector queues events or
     * coalesces them. Note that this connector makes no promises on that
     * front.
     */
    n_notify_me();
    n_notify_me();
    result = e_poll();
    assert(result == 1);
    /* Drain pending events. */
    while (e_poll());

    /* Now confirm that waiting clears any pending event. We can't easily test
     * that waiting with no event blocks because we'd get stuck.
     */
    n_notify_me();
    e_wait();
    result = e_poll();
    assert(result == 0);

    printf("All OK!\n");
    return 0;
}
