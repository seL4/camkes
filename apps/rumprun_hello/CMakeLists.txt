#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(rumprun_hello C)

includeGlobalComponents()

include(${CMAKE_CURRENT_LIST_DIR}/../rumprun_common.cmake)

DeclareExternalRumprunProject(
    hello_external
    ${CMAKE_CURRENT_LIST_DIR}/components/hello
    bin/hello)

DeclareRumprunCAmkESComponent(rumprun
    POSIX_BIN ${CMAKE_CURRENT_BINARY_DIR}/bin/hello
    BAKE_CONFIG sel4_generic
)

DeclareCAmkESRootserver(rumprun_hello.camkes CPP_INCLUDES ${CAMKES_RUMPRUN_PATH})
add_simulate_test([=[wait_for "finished sleep"]=])
