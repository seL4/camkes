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

include(cakeml)
find_package(cakeml_libs REQUIRED)
include(${LIBCAKEML_PATH})
include(${CAKEML_META_PATH})

project(cakeml_regex C)

DeclareCakeMLMetaUtils(
    ${CAKEML_LIBS_DIR}/meta_utils
    meta_utils
    meta_utils_target
    meta_utils_target_files
    meta_utils_path
)

DeclareCAmkESComponent(CakeMLFilter
    SOURCES components/CakeMLFilter/emit_string.c
    CAKEML_SOURCES components/CakeMLFilter/filterProgScript.sml components/CakeMLFilter/componentScript.sml
    CAKEML_HEAP_SIZE 100
    CAKEML_INCLUDES ${meta_utils_path} "/$(HOLDIR)/examples/formal-languages/regular" "${CAKEMLDIR}/semantics/proofs"
    CAKEML_DEPENDS meta_utils_target ${meta_utils_target_files}
)

DeclareCAmkESComponent(Producer
    SOURCES components/Producer/producer.c
)

DeclareCAmkESComponent(Consumer
    SOURCES components/Consumer/consumer.c
)

DeclareCAmkESRootserver(cakeml_regex.camkes)
