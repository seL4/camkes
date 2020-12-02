#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(aeroplage C)

if(NOT "${KernelArch}" STREQUAL "x86")
    message(FATAL_ERROR "aeroplage application only supported on x86")
endif()

DeclareCAmkESComponent(
    KeyboardDriver
    SOURCES
    components/KeyboardDriver/driver.c
    LIBS
    ringbuffer
    sel4keyboard
)
DeclareCAmkESComponent(MockLinux SOURCES components/MockLinux/mocklinux.c LIBS ringbuffer)
DeclareCAmkESComponent(Switch SOURCES components/Switch/switch.c LIBS ringbuffer)
DeclareCAmkESComponent(
    VESADriver
    SOURCES
    components/VESADriver/chars.c
    components/VESADriver/vesadriver.c
    LIBS
    ringbuffer
    sel4bga
)

DeclareCAmkESRootserver(aeroplage.camkes)
