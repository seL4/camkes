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

project(cakeml_tipc C)

include(cakeml)
find_package(cakeml_libs REQUIRED)
include(${LIBCAKEML_PATH})

includeGlobalComponents()

include(${CAKEML_META_PATH})

DeclareCakeMLMetaUtils(
    ${CMAKE_SOURCE_DIR}/projects/cakeml_libs/meta_utils
    meta_utils
    meta_utils_target
    meta_utils_target_files
    meta_utils_path
)

DeclareCAmkESComponent(Client
    SOURCES components/client/client.c
    LIBS virtqueue vswitch
)

CakeMLPP(components/cakeml-filter
        ${CMAKE_SOURCE_DIR}/projects/cakeml_libs/cakeml_libraries/libvirtqueue/virtqueueScript.sml
)

DeclareCAmkESComponent(CakeMLFilter
    CAKEML_SOURCES components/cakeml-filter/componentScript.sml
                   ${CMAKE_CURRENT_BINARY_DIR}/components/cakeml-filter/virtqueueScript.sml
    CAKEML_INCLUDES ${CAKEML_INCLUDES} ${meta_utils_path}
    SOURCES components/cakeml-filter/global_endpoint.c
    LIBS vswitch
    CAKEML_HEAP_SIZE 50
    CAKEML_DEPENDS meta_utils_target ${meta_utils_target_files}
)

DeclareCAmkESRootserver(cakeml_tipc.camkes)
