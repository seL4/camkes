/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
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
    void *fdt = ps_io_fdt_get(&dummy.io_fdt);
    int total_size = fdt_totalsize(fdt);

    void *new = malloc(total_size);
    fdtgen_context_t *handle = fdtgen_new_context(new, total_size);
    fdtgen_keep_nodes(handle, nodes_to_keep, num_nodes_to_keep);
    fdtgen_generate(handle, fdt);
    fdtgen_free_context(handle);
    fdt_pack(new);

    dump_blob(new);

    free(new);

    return 0;
}
