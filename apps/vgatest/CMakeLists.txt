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

project(vgatest C)

# This only works on x86
if(NOT "${KernelArch}" STREQUAL "x86")
    message(FATAL_ERROR "vgatest application only supported on x86")
endif()

DeclareCAmkESComponent(VGADriver SOURCES components/VGADriver/vgadriver.c)

# If a simulation target gets generated then it should have graphics enabled
SetSimulationScriptProperty(GRAPHIC TRUE)

DeclareCAmkESRootserver(vgatest.camkes)
