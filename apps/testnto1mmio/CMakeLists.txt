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

project(testnto1mmio C)

# This only works on kzm
set(KernelArch arm CACHE STRING "" FORCE)
set(KernelArmSel4Arch aarch32 CACHE STRING "" FORCE)
set(KernelARMPlatform kzm CACHE STRING "" FORCE)

DeclareCAmkESComponent(Driver1 SOURCES driver1.c INCLUDES .)
DeclareCAmkESComponent(Driver2 SOURCES driver2.c INCLUDES .)

DeclareCAmkESRootserver(testnto1mmio.camkes)
