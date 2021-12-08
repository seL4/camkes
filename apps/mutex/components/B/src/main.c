/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>
#include <stdio.h>

int lock_lock(void);
int lock_unlock(void);


static unsigned long long factorial(unsigned long long n)
{
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int run()
{
    const char *name = get_instance_name();

    printf("%s: started.\n", name);

    printf("%s: trying to acquire the lock...\n", name);
    lock_lock();
    printf("%s: got it!\n", name);

    printf("%s: Let's do some actual work (not like that other lazy instance)...\n", name);
    unsigned long long n = 20;
    unsigned long long  result = factorial(n);
    printf("%s: So, it turns out factorial %llu is %llu\n", name, n, result);
    printf("%s: Let's take a breather...\n", name);
    for (int i = 0; i < 100000; i++) {
        asm volatile("");
    }

    printf("%s: Unlocking...\n", name);
    lock_unlock();
    printf("%s: Unlocked.\n", name);
    // Yield to allow the other component to finish before printing our exit message
    // This tries to avoid the consoles getting interleaved.
    // We Yield multiple times because the connector is implemented using multiple seL4_Send and
    // seL4_Recv syscalls which put the calling thread to the back of the scheduler queue.
    seL4_Yield();
    seL4_Yield();
    lock_lock();
    lock_unlock();

    seL4_Yield();
    printf("%s: Exiting\n", name);


    return 0;
}

