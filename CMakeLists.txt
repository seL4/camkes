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
include(settings.cmake)
project(camkes C CXX ASM)

find_package(camkes-tool REQUIRED)
find_package(global-components REQUIRED)
find_package(sel4_projects_libs REQUIRED)

camkes_tool_setup_camkes_build_environment()

sel4_projects_libs_import_libraries()

function(includeGlobalComponents)
    global_components_import_project()
endfunction()

# figure out the valid apps
set(app_names "")
file(GLOB apps apps/*)
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

# We only support one application being built at a time
include(apps/${CAMKES_APP}/CMakeLists.txt)

# Should be done adding targets, can now generate the root server and the global configuration
GenerateCAmkESRootserver()
include(simulation)
if(SIMULATION)
    GenerateSimulateScript()
endif()
