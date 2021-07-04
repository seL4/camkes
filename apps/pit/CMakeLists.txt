#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(pit C)

# This requires an x86 kernel with a PIC interrupt controller
if(NOT "${KernelArch}" STREQUAL "x86")
    message(FATAL_ERROR "pit application only supported on x86")
endif()

DeclareCAmkESComponent(Driver SOURCES components/Driver/src/driver.c)

DeclareCAmkESRootserver(pit.camkes)
add_simulate_test([=[wait_for "5 seconds elapsed"]=])
