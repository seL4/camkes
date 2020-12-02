#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(rumprun_rust C)

includeGlobalComponents()

include(${CMAKE_CURRENT_LIST_DIR}/../rumprun_common.cmake)

add_custom_target(a_rumptools_target)
add_dependencies(a_rumptools_target rumprun_toplevel_support)

set(tuple $<TARGET_PROPERTY:rumprun_toplevel_support,RUMPRUN_TOOLCHAIN_TUPLE>)
set(tool_location $<TARGET_PROPERTY:rumprun_toplevel_support,RUMPRUN_TOOLCHAIN_PATH>)
set(bin_file ${CMAKE_CURRENT_BINARY_DIR}/output/rustest)
add_custom_command(
    OUTPUT ${bin_file}
    COMMAND  cd ${CMAKE_CURRENT_LIST_DIR}/components/hellorust/rustest &&
       ${CMAKE_COMMAND} -E env
        PATH=$ENV{PATH}:${tool_location}
        cargo build --target ${tuple} --target-dir ${CMAKE_CURRENT_BINARY_DIR} -Z unstable-options --out-dir ${CMAKE_CURRENT_BINARY_DIR}/output
    DEPENDS a_rumptools_target
    COMMENT "[Invoking cargo]")

DeclareRumprunCAmkESComponent(rumprun_rust
    POSIX_BIN ${bin_file}
    BAKE_CONFIG sel4_generic
)

DeclareExternalRumprunProject(
    hello_external
    ${CMAKE_CURRENT_LIST_DIR}/components/hello
    bin/hello)

DeclareRumprunCAmkESComponent(rumprun
    POSIX_BIN ${CMAKE_CURRENT_BINARY_DIR}/bin/hello
    BAKE_CONFIG sel4_generic
)

DeclareCAmkESRootserver(rumprun_rust.camkes CPP_INCLUDES ${CAMKES_RUMPRUN_PATH} include)
