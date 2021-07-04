#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

# Declare interface library for our headers
add_library(GetterIface INTERFACE)
target_include_directories(
    GetterIface
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/../common_procedure_types"
)
