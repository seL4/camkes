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

cmake_minimum_required(VERSION 3.7.2)

project(rumprun_pthreads C)


find_file(RUMPRUN_PATH rumprun PATHS ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/projects CMAKE_FIND_ROOT_PATH_BOTH)
mark_as_advanced(FORCE RUMPRUN_PATH)
if("${RUMPRUN_PATH}" STREQUAL "RUMPRUN_PATH-NOTFOUND")
    message(FATAL_ERROR "Failed to find rumprun. Consider cmake -DRUMPRUN_PATH=/path/to/rumprun")
endif()

find_file(CAMKES_HELPERS_PATH camkes_helpers.cmake PATHS ${RUMPRUN_PATH}/platform/sel4/camkes/ CMAKE_FIND_ROOT_PATH_BOTH)
mark_as_advanced(FORCE CAMKES_RUMPRUN_PATH)
if("${CAMKES_HELPERS_PATH}" STREQUAL "CAMKES_HELPERS_PATH-NOTFOUND")
    message(FATAL_ERROR "Failed to find camkes_helpers.cmake. Consider cmake -DCAMKES_HELPERS_PATH=/path/to/camkes_helpers.cmake")
endif()

include(${CAMKES_HELPERS_PATH})

add_custom_target(a_rumptools_target)
add_dependencies(a_rumptools_target rumprun_toplevel_support)

# Add ExternalProject for building a binary using rumprun toolchains
set(external_target_name rump_pthreads_external)
set(stamp_dir ${CMAKE_CURRENT_BINARY_DIR}/${external_target_name}-stamp)
ExternalProject_Add(${external_target_name}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/components/pthreads
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    STAMP_DIR ${stamp_dir}
    DEPENDS a_rumptools_target
    BUILD_ALWAYS ON
    EXCLUDE_FROM_ALL
    CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=$<TARGET_PROPERTY:rumprun_toplevel_support,RUMPRUN_TOOLCHAIN_CMAKE>
               -G Ninja
               -DCMAKE_INSTALL_PREFIX:STRING=${CMAKE_CURRENT_BINARY_DIR}
)
DeclareExternalProjObjectFiles(${external_target_name} ${CMAKE_CURRENT_BINARY_DIR} FILES bin/pthreads)

DeclareRumprunCAmkESComponent(rumprun_pthreads
    POSIX_BIN ${CMAKE_CURRENT_BINARY_DIR}/bin/pthreads
    BAKE_CONFIG sel4_generic
)

DeclareCAmkESRootserver(rumprun_pthreads.camkes CPP_INCLUDES ${CAMKES_RUMPRUN_PATH})
