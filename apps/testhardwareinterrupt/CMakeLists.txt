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

project(testhardwareinterrupt C)

# If x86 force the PIC so that legacy interrupt connector can work correctly
if (KernelArchX86)
    set(KernelIRQController PIC CACHE STRING "" FORCE)
endif()

DeclareCAmkESComponent(Software SOURCES C.c)

DeclareCAmkESRootserver(testhardwareinterrupt.camkes)
