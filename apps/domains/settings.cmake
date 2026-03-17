#
# Copyright 2026, Proofcraft Pty Ltd
#
# SPDX-License-Identifier: BSD-2-Clause
#

set(KernelNumDomains 3 CACHE STRING "" FORCE)
set(KernelDomainSchedule "${CMAKE_CURRENT_LIST_DIR}/domain_schedule.c" CACHE INTERNAL "")
