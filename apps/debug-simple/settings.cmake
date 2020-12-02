#
# Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

# The debug component relies on legacy PIC interrupts, so force that
set(KernelIRQController PIC CACHE STRING "" FORCE)
