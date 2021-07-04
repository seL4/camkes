#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(alignment C)

if(NOT "${KernelArch}" STREQUAL "x86")
    message(FATAL_ERROR "alignment application only supported on x86")
endif()

DeclareCAmkESComponent(Client SOURCES client.c common/common.S INCLUDES common)
DeclareCAmkESComponent(Server SOURCES server.c common/common.S INCLUDES common)

DeclareCAmkESRootserver(alignment.camkes)
add_simulate_test([=[wait_for "All is well in the universe!"]=])
