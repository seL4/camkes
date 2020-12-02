#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(epit C)

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
    message(FATAL_ERROR "epit application only supported on Arm sabre")
endif()

DeclareCAmkESComponent(Driver SOURCES components/Driver/src/driver.c)

DeclareCAmkESRootserver(epit.camkes)
add_simulate_test([=[wait_for "EPIT time out...6"]=])
