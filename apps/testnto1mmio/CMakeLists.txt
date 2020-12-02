#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(testnto1mmio C)

# CAmkES spec is hard coded for the sabre
if(
    NOT
    "${KernelArch}"
    STREQUAL
    "arm"
    OR
        NOT
        "${KernelARMPlatform}"
        STREQUAL
        "sabre"
)
    message(FATAL_ERROR "testnto1mmio application only supported on Arm sabre")
endif()

DeclareCAmkESComponent(Driver1 SOURCES driver1.c INCLUDES .)
DeclareCAmkESComponent(Driver2 SOURCES driver2.c INCLUDES .)

DeclareCAmkESRootserver(testnto1mmio.camkes)
add_simulate_test([=[
    wait_for "hello from drv1"
    wait_for "hello from drv2"
]=])
