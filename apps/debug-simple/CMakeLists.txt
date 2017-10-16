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

project(debug-simple C)

DeclareCAmkESComponent(Client SOURCES client.c)
DeclareCAmkESComponent(Echo SOURCES echo.c)

# We need to preprocess our .camkes spec to insert the debug components
set(CAmkESCPP ON CACHE BOOL "" FORCE)

# Need support for the hardware debug API
set(HardwareDebugAPI ON CACHE BOOL "" FORCE)

# Only support ia32 at the moment
set(KernelArch x86 CACHE STRING "" FORCE)
set(KernelX86Sel4Arch ia32 CACHE STRING "" FORCE)
# The debug component relies on legacy PIC interrupts, so force that
set(KernelIRQController PIC CACHE STRING "" FORCE)

# Since we cannot use generator expressions in CPP_FLAGS we have to hard code the include path
# that we want
DeclareCAmkESRootserver(debug-simple.camkes CPP_FLAGS -I${CMAKE_SOURCE_DIR}/tools/camkes/libsel4camkes/include)
