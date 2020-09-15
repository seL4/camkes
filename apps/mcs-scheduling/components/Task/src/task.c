/*
 * Copyright 2020, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#include <camkes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sel4bench/sel4bench.h>
#include <autoconf.h>

/* The example to demostrate MCS scheduling logic:
 * Consider 3 threads with budget and period setting as T_1(90 / 200),
 * T_2(60 / 250), and T_3(10 / 300), sorted in descending order of priority.
 * The sum of CPU utilization is 72.3% thus meeting the schedulability
 * requirement of Rate-monotonic scheduling, which means the lower priority
 * thread T_3 will always have its chance to run.
 *
 * Note: This example works well with x86_64, but not with Arm64/32.
 */

#define TEST_SIZE 30

/* The threshold to detect if the thread has been preempted and returned,
 * might need to be changed depending on the platform. Currently we only
 * tested it on x86_86 and ia32 */
#define MAGIC_CYCLES 500

int run(void)
{
    uint64_t ccounts[TEST_SIZE];
    uint64_t tss[TEST_SIZE];

    uint64_t ts, prev = (uint64_t)sel4bench_get_cycle_count();
    uint64_t ccount = 0; /* cycle count */
    int pcount = 0; /* preemption count */
    tss[0] = prev;

    while (pcount < TEST_SIZE) {
        ts = (uint64_t)sel4bench_get_cycle_count();
        assert(ts > prev); /* Should not have to handle overflow */
        uint64_t diff = ts - prev;

        if (diff < MAGIC_CYCLES) {
            COMPILER_MEMORY_FENCE();
            ccount += diff;
            COMPILER_MEMORY_FENCE();

        } else {
            ccounts[pcount] = ccount;
            pcount++;
            (pcount < TEST_SIZE) ? (tss[pcount] = ts) : 0;
            ccount = 0;
        }
        prev = ts;
    }
    ts = (uint64_t)sel4bench_get_cycle_count();

    uint64_t util = 0;
    for (int i = 0; i < TEST_SIZE; i++) {
        printf("[%s] #%d: started %llu, consumed %llu\n", get_instance_name(), i + 1, tss[i], ccounts[i]);
        util += ccounts[i];
    }
    printf("[%s] CPU utilization: %d%%\n", get_instance_name(), (util * 100) / (ts - tss[0]));
}
