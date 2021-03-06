#
# Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(picoserver C)

includeGlobalComponents()

set(LibPicotcp ON CACHE BOOL "" FORCE)
set(LibPicotcpBsd OFF CACHE BOOL "" FORCE)
set(LibEthdriverNumPreallocatedBuffers 32 CACHE STRING "" FORCE)

# For x86, we map DMA frames into the IOMMU to use as buffers for the
# Ethernet device. The VKA and VSpace libraries do not like pages that
# are not 4K in size.
set(CAmkESDMALargeFramePromotion OFF CACHE BOOL "" FORCE)

# The app has only been tested on hardware, and not on QEMU
set(SIMULATION OFF CACHE BOOL "" FORCE)
if("${KernelArch}" STREQUAL "x86")
    # The IOMMU is required for the Ethdriver component on x86
    set(KernelIOMMU ON CACHE BOOL "" FORCE)
endif()

set(CAmkESCPP ON CACHE BOOL "" FORCE)
if("${KernelArch}" STREQUAL "x86")
    set(cpp_define -DKernelArchX86)
elseif("${KernelArch}" STREQUAL "arm")
    set(cpp_define -DKernelArchArm)
endif()

set(PICOSERVER_IP_ADDR "" CACHE STRING "IP address for the Picoserver component")

DeclareCAmkESComponent(
    Echo
    SOURCES
    components/Echo/src/echo.c
    INCLUDES
    components/include/
    LIBS
    picotcp
    PicoServer-client
)
DeclareCAmkESComponent(
    Listener
    SOURCES
    components/Listener/src/listener.c
    INCLUDES
    components/include/
    LIBS
    picotcp
    PicoServer-client
)

DeclareCAmkESRootserver(
    picoserver.camkes
    CPP_FLAGS
    ${cpp_define}
    -DPICOSERVER_IP_ADDR=\"${PICOSERVER_IP_ADDR}\"
)
