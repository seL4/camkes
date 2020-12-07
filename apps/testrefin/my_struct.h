/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

/* Some large struct that we will not want to pass on our stack. Note that we
 * still need this to be able to fit into the IPC buffer for the purposes of
 * this test.
 */
typedef struct {
    int data[100];
} MyStruct;
