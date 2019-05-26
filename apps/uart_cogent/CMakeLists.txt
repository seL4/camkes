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

project(uart_cogent C)

# This only works on sabre
if(
    NOT
    "${KernelArch}"
    STREQUAL
    "arm"
    OR
        NOT
        "${KernelARMPlatform}"
        STREQUAL
        "sabre"
)
    message(FATAL_ERROR "uart application only supported on Arm sabre")
endif()

find_program(COGENT_TOOL NAMES "cogent")

set(COGENT_PATH ${CMAKE_SOURCE_DIR}/tools/cogent/cogent)

set(driver_src_dir ${CMAKE_CURRENT_LIST_DIR}/components/Driver/src/)
set(c_flags "$CPPIN -o $CPPOUT -E -P -I${COGENT_PATH}/lib")

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/serial_pp_inferred.c
    COMMAND cp ${driver_src_dir}/serial.cogent serial.cogent
    COMMAND cp ${driver_src_dir}/serial.ac serial.ac
    COMMAND
        ${COGENT_TOOL} serial.cogent -g -Od -ogenerated
        --fno-fncall-as-macro
        --ffunc-purity-attr
        --Wno-warn
        --infer-c-funcs=serial.ac
        --cpp-args=${c_flags}
        --ext-types=${driver_src_dir}/types.cfg
        --entry-funcs=${driver_src_dir}/entrypoints.cfg
    VERBATIM
    DEPENDS
        ${driver_src_dir}/serial.cogent
        ${driver_src_dir}/serial.ac
        ${driver_src_dir}/types.cfg
        ${driver_src_dir}/entrypoints.cfg
)

DeclareCAmkESComponent(Client SOURCES components/Client/src/client.c)
DeclareCAmkESComponent(
    Driver
    SOURCES
    ${CMAKE_CURRENT_BINARY_DIR}/serial_pp_inferred.c
    INCLUDES
    ${COGENT_PATH}/lib
)

DeclareCAmkESRootserver(uart.camkes)
