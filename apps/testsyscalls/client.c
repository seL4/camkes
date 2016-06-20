/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

/* Force assertions on. */
#ifdef NDEBUG
#   undef NDEBUG
#endif

#define _BSD_SOURCE /* for madvise */

#include <assert.h>
#include <camkes.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <utils/util.h>

static void test_madvise(void) {

    static char page[2 * PAGE_SIZE_4K] ALIGN(PAGE_SIZE_4K);

    /* Standard madvise on a page-aligned region. */
    int r = madvise(page, sizeof page, MADV_NORMAL);
    assert(r == 0);

    /* Confirm all the advices work. */
    r = madvise(page, sizeof page, MADV_RANDOM);
    assert(r == 0);
    r = madvise(page, sizeof page, MADV_SEQUENTIAL);
    assert(r == 0);
    r = madvise(page, sizeof page, MADV_WILLNEED);
    assert(r == 0);
    r = madvise(page, sizeof page, MADV_DONTNEED);
    assert(r == 0);

    /* XXX: Disable all the following tests because they cause writes to `errno`. Thread-local
     * storage is used to back `errno`, but the CAmkES environment does not currently implement
     * full TLS. As a result, any access to `errno` causes a segfault.
     */
    if (0) {

    /* Confirm that invalid advice is rejected. */
    const int BAD_ADVICE = -1;
    static_assert(BAD_ADVICE != MADV_NORMAL &&
                  BAD_ADVICE != MADV_RANDOM &&
                  BAD_ADVICE != MADV_SEQUENTIAL &&
                  BAD_ADVICE != MADV_WILLNEED &&
                  BAD_ADVICE != MADV_DONTNEED,
        "bad value chosen for BAD_ADVICE that collides with valid advice");
    r = madvise(page, sizeof page, BAD_ADVICE);
    assert(r == -1);
    assert(errno == EINVAL);

    /* Confirm that misaligned addresses are rejected. */
    r = madvise((void*)page + 42, PAGE_SIZE_4K, MADV_NORMAL);
    assert(r == -1);
    assert(errno == EINVAL);

    /* Confirm that regions outside our address space are rejected. */
    extern char __executable_start[1]; /* start of our address space provided by the linker. */
    void *BAD_ADDR = (void*)(PAGE_ALIGN_4K((uintptr_t)__executable_start) - PAGE_SIZE_4K);
    r = madvise(BAD_ADDR, PAGE_SIZE_4K, MADV_NORMAL);
    assert(r == -1);
    assert(errno == ENOMEM);

    }
}

int run(void) {
    test_madvise();

    printf("All OK\n");
    return 0;
}
