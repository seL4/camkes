#
# Copyright 2018, Data61
# Commonwealth Scientific and Industrial Research Organisation (CSIRO)
# ABN 41 687 119 230.
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(DATA61_BSD)
#

cmake_minimum_required(VERSION 3.8.2)

# Set some options we know we need here. Applications can override them
if (${CapDLLoaderMaxObjects} LESS 20000)
    set(CapDLLoaderMaxObjects 20000 CACHE STRING "" FORCE)
endif()
if (${KernelRootCNodeSizeBits} LESS 17)
    set(KernelRootCNodeSizeBits 17 CACHE STRING "" FORCE)
endif()
set(KernelNumDomains 1 CACHE STRING "" FORCE)

# Add our libraries
add_subdirectory(libs/libringbuffer)
add_subdirectory(libs/libsel4keyboard)
add_subdirectory(libs/libsel4bga)

# Make sure CAMKES_APP is definition that can be changed in the ccmake-gui
set(CAMKES_APP "${CAMKES_APP}" CACHE STRING "CAmkES application to build")

# Define some meta options
set(SIMULATION ON CACHE BOOL "Try and use simultable features")
set(RELEASE OFF CACHE BOOL "Performance optimized build")
set(PLATFORM "x86_64" CACHE STRING "Platform to use")
set(valid_arm_platform "sabre;kzm")
set_property(CACHE PLATFORM PROPERTY STRINGS "${KernelX86Sel4Arch_all_strings};${valid_arm_platform}")

if ("${PLATFORM}" IN_LIST KernelX86Sel4Arch_all_strings)
    set(KernelArch x86 CACHE STRING "" FORCE)
    set(KernelX86Sel4Arch ${PLATFORM} CACHE STRING "" FORCE)
elseif ("${PLATFORM}" IN_LIST valid_arm_platform)
    set(KernelArch arm CACHE STRING "" FORCE)
    set(KernelArmSel4Arch aarch32 CACHE STRING "" FORCE)
    set(KernelARMPlatform ${PLATFORM} CACHE STRING "" FORCE)
    if ((NOT ARM) AND (NOT AARCH32) AND ("${CROSS_COMPILER_PREFIX}" STREQUAL ""))
        message(WARNING "Looks like you building for ARM without using a cross compiler")
    endif()
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

if (SIMULATION)
    ApplyCommonSimulationSettings()
    GenerateSimulateScript()
endif()

ApplyCommonReleaseVerificationSettings(${RELEASE} FALSE)

ApplyData61ElfLoaderSettings()

# We only support one application being built at a time
add_subdirectory(apps/${CAMKES_APP})
