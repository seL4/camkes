#
# Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

set(LibLwip ON CACHE BOOL "" FORCE)
set(LibEthdriverNumPreallocatedBuffers 32 CACHE STRING "" FORCE)

# For x86, we map DMA frames into the IOMMU to use as buffers for the
# Ethernet device. The VKA and VSpace libraries do not like pages that
# are not 4K in size.
set(CAmkESDMALargeFramePromotion OFF CACHE BOOL "" FORCE)

# This application only works on hardware at the moment, not simulation
# set(SIMULATION OFF CACHE BOOL "" FORCE)
if("${KernelArch}" STREQUAL "x86")
    # The IOMMU is required for the Ethdriver component on x86
    set(KernelIOMMU ON CACHE BOOL "" FORCE)
endif()

set(cpp_define -DKernelArchArm)

set(LibEthdriverRXDescCount 256 CACHE STRING "" FORCE)
set(LibEthdriverTXDescCount 256 CACHE STRING "" FORCE)
set(CAmkESNoFPUByDefault ON CACHE BOOL "" FORCE)
