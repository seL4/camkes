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

project(hellorust C)

# Only support x86_64 at the moment
set(KernelArch x86 CACHE STRING "" FORCE)
set(KernelX86Sel4Arch x86_64 CACHE STRING "" FORCE)

RustAddLibrary(main
	SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/components/main
	TARGET x86_64-sel4-none
	LIB_FILENAME libmain.a
	)

DeclareCAmkESComponent(main LIBS main)

DeclareCAmkESRootserver(hellorust.camkes)
