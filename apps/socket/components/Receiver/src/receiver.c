/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <stdio.h>
#include <string.h>
#include <sync/spinlock.h>

int run(void) {
    const char *name = get_instance_name();

    printf("%s: Waiting for transport init...\n", name);
    setup_wait();

    printf("%s: Waiting for data...\n", name);
    int received = 0;
    while (!received) {
        sync_spinlock_lock((sync_spinlock_t*)&sock->lock);
        if (sock->full) {
            printf("%s: Received \"%s\".\n", name, sock->data);
            received = 1;
        }
        sync_spinlock_unlock((sync_spinlock_t*)&sock->lock);
    }

    printf("%s: Done.\n", name);
    return 0;
}
