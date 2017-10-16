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

# Exclude this project in ARM builds as it will have no sources and thus not be a valid library

if (KernelArchX86)

    project(libsel4bga C)

    file(GLOB deps src/arch-${KernelArch}/*.c)

    list(SORT deps)

    add_library(sel4bga STATIC EXCLUDE_FROM_ALL ${deps})
    target_include_directories(sel4bga PUBLIC "arch_include/${KernelArch}")
    target_link_libraries(sel4bga muslc)

endif()
