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

project(rumprun_hello C)

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
