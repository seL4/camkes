#
# Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.8.2)

project(lwipserver_single C)
includeGlobalComponents()

find_package(projects_libs REQUIRED)

set(CAmkESCPP ON CACHE BOOL "" FORCE)
if(KernelArchX86)
    set(cpp_define -DKernelArchX86)
elseif(KernelArchARM)
    set(cpp_define -DKernelArchArm)
endif()

include(${LWIP_HELPERS})
AddLWIPConfiguration(${CMAKE_CURRENT_LIST_DIR}/lwip_include)

set(libs sel4utils sel4vka sel4allocman sel4vspace sel4simple sel4platsupport lwip)

set(sources src/tcp_echo_socket.c src/udp_echo_socket.c src/utilization_socket.c)

DeclareCAmkESComponent(
    LWIPServer
    SOURCES
    ${sources}
    INCLUDES
    include
    LIBS
    ${libs}
    LD_FLAGS
    -Wl,--section-start=.note.gnu.build-id=0x400920 #Ensure reproducible build
)

CAmkESAddCPPInclude("${CMAKE_CURRENT_LIST_DIR}/include/")

if(KernelSel4ArchX86_64)
    DeclareCAmkESComponent(Ethdriver82574DF SOURCES x86_64_eth_init.c LIBS "${ETHDRIVER_LIBS}")
    DeclareCAmkESRootserver(lwipserver2_x86_64.camkes CPP_FLAGS ${cpp_define})
elseif(KernelPlatformImx8mm-evk)
    DeclareCAmkESRootserver(lwipserver2_imx8mm.camkes CPP_FLAGS ${cpp_define})
else()
    message(FATAL_ERROR "Unsupported platform.")
endif()
