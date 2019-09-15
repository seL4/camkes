#
# Copyright 2019, Data61
# Commonwealth Scientific and Industrial Research Organisation (CSIRO)
# ABN 41 687 119 230.
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(DATA61_BSD)
#

cmake_minimum_required(VERSION 3.7.2)

set(project_dir "${CMAKE_CURRENT_LIST_DIR}/../../")
file(GLOB project_modules ${project_dir}/projects/*)
list(
    APPEND
        CMAKE_MODULE_PATH
        ${project_dir}/kernel
        ${project_dir}/tools/seL4/cmake-tool/helpers/
        ${project_dir}/tools/seL4/elfloader-tool/
        ${project_modules}
)

set(PICOTCP_PATH "${project_dir}/projects/picotcp" CACHE INTERNAL "")
set(BBL_PATH ${project_dir}/tools/riscv-pk CACHE STRING "BBL Folder location")
set(COGENT_PATH ${project_dir}/tools/cogent/cogent CACHE INTERNAL "")

set(SEL4_CONFIG_DEFAULT_ADVANCED ON)

include(application_settings)
include(${CMAKE_CURRENT_LIST_DIR}/easy-settings.cmake)

# Set some options we know we need here. Applications can override them
if(("${CapDLLoaderMaxObjects}" STREQUAL "") OR ("${CapDLLoaderMaxObjects}" LESS 20000))
    set(CapDLLoaderMaxObjects 20000 CACHE STRING "" FORCE)
endif()
if(("${KernelRootCNodeSizeBits}" STREQUAL "") OR ("${KernelRootCNodeSizeBits}" LESS 17))
    set(KernelRootCNodeSizeBits 17 CACHE STRING "" FORCE)
endif()
set(KernelNumDomains 1 CACHE STRING "" FORCE)

# Define some meta options
set(valid_arm_platform "am335x;sabre;kzm;exynos5410;exynos5422;tx1;tx2;zynq7000")
set(valid_x86_platform "ia32;x86_64")
set(valid_riscv_platform "spike")
set(valid_platforms "${valid_x86_platform};${valid_arm_platform};${valid_riscv_platform}")
set_property(CACHE PLATFORM PROPERTY STRINGS "${valid_platforms}")
list(FIND valid_platforms "${PLATFORM}" index)
if("${index}" STREQUAL "-1")
    message(FATAL_ERROR "Invalid PLATFORM selected: \"${PLATFORM}\"
Valid platforms are: \"${valid_platforms}\"")
endif()

correct_platform_strings()

if(ARM_HYP)
    set(KernelArmHypervisorSupport ON CACHE BOOL "" FORCE)
endif()

find_package(seL4 REQUIRED)
sel4_configure_platform_settings()

if(KernelArchARM)
    ApplyData61ElfLoaderSettings(${KernelPlatform} ${KernelSel4Arch})
endif()

if(SIMULATION)
    ApplyCommonSimulationSettings(${KernelArch})
endif()

ApplyCommonReleaseVerificationSettings(${RELEASE} FALSE)

# If an application specific settings file exists then import it here.
# This can be used for applications to configure the kernel in specific ways
include(${CMAKE_CURRENT_LIST_DIR}/apps/${CAMKES_APP}/settings.cmake OPTIONAL)
