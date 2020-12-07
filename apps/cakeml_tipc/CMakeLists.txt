#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(cakeml_tipc C)

include(cakeml)
find_package(cakeml_libs REQUIRED)
include(${LIBCAKEML_PATH})

includeGlobalComponents()

include(${CAKEML_META_PATH})

DeclareCakeMLMetaUtils(
    ${CAKEML_LIBS_DIR}/meta_utils
    meta_utils
    meta_utils_target
    meta_utils_target_files
    meta_utils_path
)

DeclareCAmkESComponent(Client SOURCES components/client/client.c LIBS virtqueue vswitch)

CakeMLPP(
    components/cakeml-filter ${CAKEML_LIBS_DIR}/cakeml_libraries/libvirtqueue/virtqueueScript.sml
)

DeclareCAmkESComponent(
    CakeMLFilter
    CAKEML_SOURCES
    components/cakeml-filter/componentScript.sml
    ${CMAKE_CURRENT_BINARY_DIR}/components/cakeml-filter/virtqueueScript.sml
    CAKEML_INCLUDES
    ${CAKEML_INCLUDES}
    ${meta_utils_path}
    SOURCES
    components/cakeml-filter/global_endpoint.c
    LIBS
    vswitch
    CAKEML_HEAP_SIZE
    50
    CAKEML_DEPENDS
    meta_utils_target
    ${meta_utils_target_files}
)

DeclareCAmkESRootserver(cakeml_tipc.camkes)
add_simulate_test([=[wait_for "Client 0 recieved payload value: 20"]=])
