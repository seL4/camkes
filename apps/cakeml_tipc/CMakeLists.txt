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

find_file(LIBCAKEML_PATH libcakeml_helpers.cmake PATHS ${CMAKE_SOURCE_DIR}/projects/cakeml_libs/ CMAKE_FIND_ROOT_PATH_BOTH)
mark_as_advanced(FORCE LIBCAKEML_PATH)
if("${LIBCAKEML_PATH}" STREQUAL "LIBCAKEML_PATH-NOTFOUND")
    message(FATAL_ERROR "Failed to find libcakeml_helpers.cmake. Consider cmake -DLIBCAKEML_PATH=/path/to/libcakeml_helpers.cmake")
endif()
include(${LIBCAKEML_PATH})

find_file(GLOBAL_COMPONENTS_PATH global-components.cmake PATHS ${CMAKE_SOURCE_DIR}/projects/global-components/ CMAKE_FIND_ROOT_PATH_BOTH)
mark_as_advanced(FORCE GLOBAL_COMPONENTS_PATH)
if("${GLOBAL_COMPONENTS_PATH}" STREQUAL "GLOBAL_COMPONENTS_PATH-NOTFOUND")
    message(FATAL_ERROR "Failed to find global-components.cmake. Consider cmake -DGLOBAL_COMPONENTS_PATH=/path/to/global-components.cmake")
endif()
include(${GLOBAL_COMPONENTS_PATH})

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
    CAKEML_INCLUDES ${CAKEMLDIR}/semantics/alt_semantics
    SOURCES components/cakeml-filter/global_endpoint.c
    LIBS vswitch
    CAKEML_HEAP_SIZE 50
)

DeclareCAmkESRootserver(cakeml_tipc.camkes)
