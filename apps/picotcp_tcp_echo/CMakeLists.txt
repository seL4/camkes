#
# Copyright 2019, Data61
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

project(picotcp_tcp_echo C)

includeGlobalComponents()

set(CAmkESCPP ON CACHE BOOL "" FORCE)
if("${KernelArch}" STREQUAL "x86")
    set(cpp_define -DKernelArchX86)
elseif("${KernelArch}" STREQUAL "arm")
    set(cpp_define -DKernelArchArm)
endif()

set(PICOSERVER_IP_ADDR "" CACHE STRING "IP address for the Picoserver component")

DeclareCAmkESComponent(Echo SOURCES components/Echo/src/echo.c INCLUDES components/include/)

if(KernelSel4ArchX86_64)

    DeclareCAmkESComponent(Ethdriver82574DF SOURCES x86_64_eth_init.c LIBS "${ETHDRIVER_LIBS}")

    DeclareCAmkESRootserver(
        picotcp_tcp_echo_x86_64.camkes
        CPP_FLAGS
        ${cpp_define}
        -DPICOSERVER_IP_ADDR=\"${PICOSERVER_IP_ADDR}\"
    )
elseif(KernelPlatformTx2)
    DeclareCAmkESRootserver(
        picotcp_tcp_echo_tx2.camkes
        CPP_FLAGS
        ${cpp_define}
        -DPICOSERVER_IP_ADDR=\"${PICOSERVER_IP_ADDR}\"
    )
else()
    message(
        FATAL_ERROR
            "Unsupported platform. This example expands some Camkes includes into a single file "
            "for demonstration purposes and so only demonstrates a subset of available platforms."
    )
endif()
