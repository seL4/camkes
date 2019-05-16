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

project(uart C)

# This only works on kzm
if(
    NOT
    "${KernelArch}"
    STREQUAL
    "arm"
    OR
        NOT
        "${KernelARMPlatform}"
        STREQUAL
        "kzm"
)
    message(FATAL_ERROR "uart application only supported on Arm kzm")
endif()

DeclareCAmkESComponent(Client SOURCES components/Client/src/client.c)
DeclareCAmkESComponent(Driver SOURCES components/Driver/src/driver.c)

DeclareCAmkESRootserver(uart.camkes)
