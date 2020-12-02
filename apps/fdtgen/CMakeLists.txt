#
# Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(fdtgen C)

# This only works on sabre
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
    message(FATAL_ERROR "fdtgen application is only supported on Arm sabre")
endif()

set(CAmkESDTS ON CACHE BOOL "" FORCE)

DeclareCAmkESComponent(Client SOURCES fdtgen.c fdt_utils.c LIBS fdtgen)

DeclareCAmkESRootserver(fdtgen.camkes)
add_simulate_test([=[
    wait_for "interrupt-controller@a01000"
    wait_for "ccm@20c4000"
    wait_for "gpc@20dc000"
    wait_for "ethernet@2188000"
    wait_for "usdhc@2190000"
    wait_for "cpus"
]=])
