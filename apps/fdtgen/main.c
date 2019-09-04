/*
 * Copyright 2019, Data61
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
#include <camkes.h>
#include <stdbool.h>
#include <assert.h>
#include <fdtgen.h>
#include <libfdt.h>
#include "fdt_utils.h"

static const char *nodes_to_keep[] = {"/soc/aips-bus@2100000/ethernet@2188000", "/cpus", "/soc/aips-bus@2100000/usdhc@2190000"};
static const int num_nodes_to_keep = sizeof(nodes_to_keep) / sizeof(char *);

int run(void)
{
    ps_io_ops_t dummy;
    camkes_io_ops(&dummy);
    void *fdt = dummy.io_fdt.cookie;

    void *new = malloc(0x10000);
    fdtgen_t *handle = fdtgen_new(new, 0x10000);
    fdtgen_keep_nodes(handle, nodes_to_keep, num_nodes_to_keep);
    fdtgen_generate(handle, fdt);
    fdtgen_cleanup(handle);
    fdt_pack(new);

    dump_blob(new);

    free(new);

    return 0;
}
