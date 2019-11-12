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

project(hellorust C)

include(rust)

if ("${KernelSel4Arch}" STREQUAL "x86_64")
    set(RUST_ARCH "x86_64-sel4-none")
elseif("${KernelSel4Arch}" STREQUAL "aarch64")
    set(RUST_ARCH "aarch64-sel4-none")
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
