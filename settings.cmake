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
set(RUMPRUN_PATH ${project_dir}/tools/rumprun CACHE INTERNAL "")

set(SEL4_CONFIG_DEFAULT_ADVANCED ON)

include(application_settings)
include(${CMAKE_CURRENT_LIST_DIR}/easy-settings.cmake)

# figure out the valid apps
set(app_names "")
file(GLOB apps ${CMAKE_CURRENT_LIST_DIR}/apps/*)
foreach(ARG ${apps})
    get_filename_component(filename ${ARG} NAME)
    list(APPEND app_names "${filename}")
endforeach()
string(
    REPLACE
        ";"
        "\n  "
        app_names_error
        "${app_names}"
)

if("${CAMKES_APP}" STREQUAL "")
    message(
        FATAL_ERROR "Missing option -DCAMKES_APP=<app> to build. Valid apps:\n  ${app_names_error}"
    )
endif()

list(FIND app_names "${CAMKES_APP}" app_exists)
if(${app_exists} EQUAL -1)
    message(
        FATAL_ERROR
            "Invalid value for option -DCAMKES_APP=${CAMKES_APP}. Valid options:\n  ${app_names_error}"
    )
endif()

if(ARM_HYP)
    set(KernelArmHypervisorSupport ON CACHE BOOL "" FORCE)
endif()

correct_platform_strings()

find_package(seL4 REQUIRED)
sel4_configure_platform_settings()

set(valid_platforms ${KernelPlatform_all_strings} ${correct_platform_strings_platform_aliases})
set_property(CACHE PLATFORM PROPERTY STRINGS ${valid_platforms})
if(NOT "${PLATFORM}" IN_LIST valid_platforms)
    message(FATAL_ERROR "Invalid PLATFORM selected: \"${PLATFORM}\"
Valid platforms are: \"${valid_platforms}\"")
endif()

if(SIMULATION)
    ApplyCommonSimulationSettings(${KernelArch})
endif()

ApplyCommonReleaseVerificationSettings(${RELEASE} FALSE)

# If an application specific settings file exists then import it here.
# This can be used for applications to configure the kernel in specific ways
include(${CMAKE_CURRENT_LIST_DIR}/apps/${CAMKES_APP}/settings.cmake OPTIONAL)
