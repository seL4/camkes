#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(hellorust C)

include(rust)

if("${KernelSel4Arch}" STREQUAL "x86_64")
    set(RUST_ARCH "x86_64-sel4-none")
elseif("${KernelSel4Arch}" STREQUAL "aarch64")
    set(RUST_ARCH "aarch64-sel4-none")
elseif("${KernelSel4Arch}" STREQUAL "aarch32")
    set(RUST_ARCH "aarch32-sel4-none")
else()
    message(FATAL_ERROR "hellorust application not supported on ${KernelSel4Arch}")
endif()

RustAddLibrary(
    main
    SOURCE_DIR
    ${CMAKE_CURRENT_LIST_DIR}/components/main
    TARGET
    ${RUST_ARCH}
    LIB_FILENAME
    libmain.a
)

DeclareCAmkESComponent(main LIBS main)

DeclareCAmkESRootserver(hellorust.camkes)
add_simulate_test([=[wait_for "Hello, world!!"]=])
