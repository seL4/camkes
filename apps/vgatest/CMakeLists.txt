#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(vgatest C)

# This only works on x86
if(NOT "${KernelArch}" STREQUAL "x86")
    message(FATAL_ERROR "vgatest application only supported on x86")
endif()

DeclareCAmkESComponent(VGADriver SOURCES components/VGADriver/vgadriver.c)

# If a simulation target gets generated then it should have graphics enabled
include(simulation)
SetSimulationScriptProperty(GRAPHIC TRUE)

DeclareCAmkESRootserver(vgatest.camkes)
