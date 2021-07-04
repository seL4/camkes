#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(reverse C)

add_compile_options("-I${CMAKE_CURRENT_SOURCE_DIR}/../../include")
add_executable(reverse tcp_server.c)

install(TARGETS reverse RUNTIME DESTINATION bin)
