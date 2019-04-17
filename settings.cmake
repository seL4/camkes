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
set(CMAKE_C_STANDARD 11)

# Set some options we know we need here. Applications can override them
if(("${CapDLLoaderMaxObjects}" STREQUAL "") OR ("${CapDLLoaderMaxObjects}" LESS 20000))
    set(CapDLLoaderMaxObjects 20000 CACHE STRING "" FORCE)
endif()
if(("${KernelRootCNodeSizeBits}" STREQUAL "") OR ("${KernelRootCNodeSizeBits}" LESS 17))
    set(KernelRootCNodeSizeBits 17 CACHE STRING "" FORCE)
endif()
set(KernelNumDomains 1 CACHE STRING "" FORCE)

# Make sure CAMKES_APP is definition that can be changed in the ccmake-gui
set(CAMKES_APP "${CAMKES_APP}" CACHE STRING "CAmkES application to build")

# Define some meta options
set(SIMULATION ON CACHE BOOL "Try and use simultable features")
set(RELEASE OFF CACHE BOOL "Performance optimized build")
set(PLATFORM "x86_64" CACHE STRING "Platform to use")
set(valid_arm_platform "sabre;kzm;exynos5410;exynos5422;tx1;zynq7000")
set(valid_x86_platform "ia32;x86_64")
set(valid_riscv_platform "spike")
set_property(
    CACHE PLATFORM
    PROPERTY STRINGS "${valid_x86_platform};${valid_arm_platform};${valid_riscv_platform}"
)

if("${PLATFORM}" IN_LIST valid_x86_platform)
    set(KernelArch x86 CACHE STRING "" FORCE)
    set(KernelX86Sel4Arch ${PLATFORM} CACHE STRING "" FORCE)
elseif("${PLATFORM}" IN_LIST valid_riscv_platform)
    set(KernelArch riscv CACHE STRING "" FORCE)
    set(KernelRiscVPlatform ${PLATFORM} CACHE STRING "" FORCE)
    if(RISCV64)
        set(KernelRiscVSel4Arch riscv64 CACHE STRING "" FORCE)
    elseif(RISCV32)
        set(KernelRiscVSel4Arch riscv32 CACHE STRING "" FORCE)
    else()
        message(FATAL_ERROR "No valid seL4_arch for PLATFORM: \"${PLATFORM}\"")
    endif()
elseif("${PLATFORM}" IN_LIST valid_arm_platform)
    set(KernelArch arm CACHE STRING "" FORCE)
    set(KernelARMPlatform ${PLATFORM} CACHE STRING "" FORCE)
    if(ARM_HYP)
        set(KernelArmHypervisorSupport ON CACHE BOOL "" FORCE)
    endif()
    if(AARCH32 OR ARM)
        if(ARM_HYP)
            set(KernelArmSel4Arch arm_hyp CACHE STRING "" FORCE)
        else()
            set(KernelArmSel4Arch aarch32 CACHE STRING "" FORCE)
        endif()
    elseif(AARCH64)
        set(KernelArmSel4Arch aarch64 CACHE STRING "" FORCE)
    endif()
    if((NOT ARM) AND (NOT AARCH32) AND (NOT AARCH64) AND ("${CROSS_COMPILER_PREFIX}" STREQUAL ""))
        message(WARNING "Looks like you are building for ARM without using a cross-compiler")
    endif()
    ApplyData61ElfLoaderSettings(${KernelARMPlatform} ${KernelArmSel4Arch})
else()
    message(FATAL_ERROR "Unsupported platform \"${PLATFORM}\"")
endif()

if(SIMULATION)
    ApplyCommonSimulationSettings(${KernelArch})
endif()

ApplyCommonReleaseVerificationSettings(${RELEASE} FALSE)
