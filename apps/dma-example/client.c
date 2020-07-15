/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#include <stdio.h>
#include <stdlib.h>
#include <camkes.h>
#include <camkes/dma.h>

int run(void) {
    printf("Starting client...\n");

    /* Test the legacy allocation functions. */

    printf("Allocating some DMA pages...\n");
    void *buffers[100];
    int i;
    for (i = 0; i < sizeof(buffers) / sizeof(void*); i++) {
        buffers[i] = camkes_dma_alloc(4096, 4096, true);
        if (buffers[i] == NULL) {
            printf("Ran out of memory after %d of them\n", i);
            break;
        }
    }

    printf("Reversing some offsets into them...\n");
    for (int j = 0; j < i; j++) {
        printf(" vaddr %p reversed to %p\n", buffers[j] + j * 13, (void*)camkes_dma_get_paddr(buffers[j] + j * 13));
    }

    printf("Freeing them...\n");
    for (int j = 0; j < i; j++) {
        camkes_dma_free(buffers[j], 4096);
    }

    /* Test the newer API. */
    printf("Attempting to allocate 0x2000...");
    void *p = camkes_dma_alloc(0x2000, 0, true);
    /* This is not guaranteed to work, but does so coincidentally. Assert on
     * this for now to catch accidental regressions in this behaviour.
     */
    assert(p != NULL && "DMA allocation >4K failed");
    if (p == NULL) {
        printf("Failed\n");
    } else {
        printf("%p\nReversing some offsets...\n", p);
        for (int j = 0; j < 7; j++) {
            printf(" vaddr %p reversed to %p\n", p + j * 0x513,
                (void*)camkes_dma_get_paddr(p + j * 0x513));
        }
        camkes_dma_free(p, 0x2000);
    }

    printf("Freeing NULL...\n");
    camkes_dma_free(NULL, /* irrelevant */ 0x20000);

    printf("Allocating with different alignment requirements...\n");
    for (int j = 0; j < 14; j++) {
        printf(" Allocating 0x1000 with alignment %d...", 1<<j);
        void *p = camkes_dma_alloc(0x1000, 1<<j, true);
        if (p == NULL) {
            printf("Failed\n");
        } else {
            printf("%p\n", p);
            camkes_dma_free(p, 0x1000);
        }
    }

    printf("Allocating 4MB...\n");
    p = camkes_dma_alloc(4 * 1024 * 1024, 0, true);
    if (p == NULL) {
        printf("Failed\n");
    } else {
        printf("Succeeded\n");
        camkes_dma_free(p, 4 * 1024 * 1024);
    }

    printf("Done.\n");
    return 0;
}
