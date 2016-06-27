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
#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <utils/util.h>

extern char __executable_start[1]; /* start of our address space provided by the linker. */

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
    void *BAD_ADDR = (void*)(PAGE_ALIGN_4K((uintptr_t)__executable_start) - PAGE_SIZE_4K);
    r = madvise(BAD_ADDR, PAGE_SIZE_4K, MADV_NORMAL);
    assert(r == -1);
    assert(errno == ENOMEM);

    }
}

static void test_mincore(void) {

    static char page[2 * PAGE_SIZE_4K] ALIGN(PAGE_SIZE_4K);

    /* Standard mincore on a page-aligned region. */
    unsigned char vec[sizeof page / PAGE_SIZE_4K] = { 0 };
    int r = mincore(page, sizeof page, vec);
    assert(r == 0);
    assert(vec[0] & 1);
    assert(vec[1] & 1);

    /* Mincore on a non-page-sized region. */
    memset(vec, 0, sizeof vec);
    r = mincore(page, sizeof page - 42, vec);
    assert(r == 0);
    assert(vec[0] & 1);
    assert(vec[1] & 1);

    /* XXX: As with the madvise tests, we need to disable these to avoid touching TLS. */
    if (0) {

    /* Confirm an invalid vec is detected. */
    r = mincore(page, sizeof page, NULL);
    assert(r == -1);
    assert(errno == EFAULT);

    r = mincore(page, sizeof page, (unsigned char*)UINTPTR_MAX);
    assert(r == -1);
    assert(errno == EFAULT);

    /* Confirm an invalid addr is detected. */
    r = mincore((void*)page + 42, sizeof page - 42, vec);
    assert(r == -1);
    assert(errno == EINVAL);

    /* Confirm an invalid length is detected. */
    r = mincore(page, SIZE_MAX, vec);
    assert(r == -1);
    assert(errno == ENOMEM);

    /* Confirm an unmapped region is detected. */
    void *BAD_ADDR = (void*)(PAGE_ALIGN_4K((uintptr_t)__executable_start) - PAGE_SIZE_4K);
    r = mincore(BAD_ADDR, PAGE_SIZE_4K, vec);
    assert(r == -1);
    assert(errno == ENOMEM);

    }
}

static void test_mlock(void) {

    static char page[2 * PAGE_SIZE_4K] ALIGN(PAGE_SIZE_4K);

    /* Standard mlock on a page-aligned region. */
    int r = mlock(page, sizeof page);
    assert(r == 0);

    /* Mlock on a non-page-sized region. */
    r = mlock(page, sizeof page - 42);
    assert(r == 0);

    /* XXX: As with the madvise tests, we need to disable these to avoid touching TLS. */
    if (0) {

    /* Confirm an invalid addr is detected. */
    r = mlock((void*)page + 42, sizeof page - 42);
    assert(r == -1);
    assert(errno == EINVAL);

    /* Confirm an invalid length is detected. */
    r = mlock(page, SIZE_MAX);
    assert(r == -1);
    assert(errno == ENOMEM);

    /* Confirm an unmapped region is detected. */
    void *BAD_ADDR = (void*)(PAGE_ALIGN_4K((uintptr_t)__executable_start) - PAGE_SIZE_4K);
    r = mlock(BAD_ADDR, PAGE_SIZE_4K);
    assert(r == -1);
    assert(errno == ENOMEM);

    }
}

static void test_munlock(void) {

    static char page[2 * PAGE_SIZE_4K] ALIGN(PAGE_SIZE_4K);

    /* Standard munlock on a page-aligned region. */
    int r = munlock(page, sizeof page);
    assert(r == 0);

    /* Munlock on a non-page-sized region. */
    r = munlock(page, sizeof page - 42);
    assert(r == 0);

    /* XXX: As with the madvise tests, we need to disable these to avoid touching TLS. */
    if (0) {

    /* Confirm an invalid addr is detected. */
    r = munlock((void*)page + 42, sizeof page - 42);
    assert(r == -1);
    assert(errno == EINVAL);

    /* Confirm an invalid length is detected. */
    r = munlock(page, SIZE_MAX);
    assert(r == -1);
    assert(errno == ENOMEM);

    /* Confirm an unmapped region is detected. */
    void *BAD_ADDR = (void*)(PAGE_ALIGN_4K((uintptr_t)__executable_start) - PAGE_SIZE_4K);
    r = munlock(BAD_ADDR, PAGE_SIZE_4K);
    assert(r == -1);
    assert(errno == ENOMEM);

    }
}

static void test_mlockall(void) {

    /* Standard mlockall. */
    int r = mlockall(MCL_CURRENT);
    assert(r == 0);

    r = mlockall(MCL_FUTURE);
    assert(r == 0);

    r = mlockall(MCL_CURRENT|MCL_FUTURE);
    assert(r == 0);

    /* XXX: As with the madvise tests, we need to disable these to avoid touching TLS. */
    if (0) {

    /* Confirm invalid flags are rejected. */
    static const int BAD_FLAGS = -1;
    static_assert((BAD_FLAGS & ~(MCL_CURRENT|MCL_FUTURE)) != 0,
        "bad value chosen for BAD_FLAGS that collides with valid flags");
    r = mlockall(BAD_FLAGS);
    assert(r == -1);
    assert(errno == EINVAL);

    }
}

static void test_munlockall(void) {

    /* Standard munlockall. */
    int r = munlockall();
    assert(r == 0);
}

static void test_getpid(void) {
    /* Check that our PID is what we expect. */
    pid_t pid = getpid();
    assert(pid == 2);
}

static void test_getppid(void) {
    /* Check that our parent is the CapDL initialiser. */
    pid_t pid = getppid();
    assert(pid == 1);
}

int run(void) {
    test_madvise();

    test_mincore();

    test_mlock();

    test_munlock();

    test_mlockall();

    test_munlockall();

    test_getpid();

    test_getppid();

    /* Run tests in other component. */
    other_call();

    printf("All OK\n");
    return 0;
}
