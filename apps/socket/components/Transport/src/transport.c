/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <stdio.h>
#include <string.h>
#include <sync/spinlock.h>

int run(void) {
    const char *name = get_instance_name();

    printf("%s: Waiting for client init...\n", name);
    setup_wait();

    printf("%s: Initialising lock...\n", name);
    sync_spinlock_init((sync_spinlock_t*)&outgoing->lock);

    printf("%s: Notifying receiver...\n", name);
    init_emit();

    printf("%s: Waiting for data...\n", name);
    int received = 0;
    while (!received) {
        sync_spinlock_lock((sync_spinlock_t*)&incoming->lock);
        if (incoming->full) {
            sync_spinlock_lock((sync_spinlock_t*)&outgoing->lock);
            strcpy((char*)outgoing->data, (char*)incoming->data);
            outgoing->full = 1;
            sync_spinlock_unlock((sync_spinlock_t*)&outgoing->lock);
            received = 1;
        }
        sync_spinlock_unlock((sync_spinlock_t*)&incoming->lock);
    }

    printf("%s: Done.\n", name);
    return 0;
}
