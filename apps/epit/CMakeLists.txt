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
