#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(rumprun_ethernet C)

DeclareCAmkESComponent(Server SOURCES components/reverse_string/server.c INCLUDES include)

includeGlobalComponents()

include(${CMAKE_CURRENT_LIST_DIR}/../rumprun_common.cmake)

DeclareExternalRumprunProject(
    rump_ether_external ${CMAKE_CURRENT_LIST_DIR}/components/rump_ether bin/reverse
)

DeclareRumprunCAmkESComponent(
    rumprun_ether
    POSIX_BIN
    ${CMAKE_CURRENT_BINARY_DIR}/bin/reverse
    BAKE_CONFIG
    sel4_ethernet
    PUBLIC_SYMBOLS
    camkes_buffer*
    camkes_ev*
    camkes_ev1*
)

DeclareCAmkESRootserver(rumprun_ethernet.camkes CPP_INCLUDES ${CAMKES_RUMPRUN_PATH} include)
add_simulate_test([=[
    wait_for "!dlroW ,olleH"
    wait_for "Server is listening on 6666"
]=])
