#
# Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

# If x86 force the PIC so that legacy interrupt connector can work correctly
if(KernelArchX86)
    set(KernelIRQController PIC CACHE STRING "" FORCE)
endif()
