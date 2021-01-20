#
# Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.8.2)

project(picotcp_smmu C)
includeGlobalComponents()

set(CAmkESCPP ON CACHE BOOL "" FORCE)
set(PICOSERVER_IP_ADDR "" CACHE STRING "IP address for the Picoserver component")

CAmkESAddCPPInclude("${CMAKE_CURRENT_LIST_DIR}/src/")

set(libs sel4utils sel4vka sel4allocman sel4vspace sel4simple sel4platsupport ethdrivers)

set(sources src/ethdriver.c src/udp_echo_socket.c)

DeclareCAmkESComponent(EthdriverARMPlat_1 SOURCES ${sources} INCLUDES include LIBS "${libs}")

DeclareCAmkESRootserver(
    Ethdriver.camkes
    CPP_FLAGS
    ${cpp_define}
    -DPICOSERVER_IP_ADDR=\"${PICOSERVER_IP_ADDR}\"
)
