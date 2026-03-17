/*
 * Copyright 2026, Proofcraft Pty Ltd
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

/* This is compiled into the kernel, so it is referencing kernel headers. */

#include <config.h>
#include <object/structures.h>
#include <model/statedata.h>

const dschedule_t ksDomSchedule[] = {
    { .domain = 0, .length = 3 },
    { .domain = 1, .length = 4 },
    { .domain = 2, .length = 1 },
};

const word_t ksDomScheduleLength = sizeof(ksDomSchedule) / sizeof(dschedule_t);
