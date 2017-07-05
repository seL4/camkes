#
# Copyright 2017, Data61
# Commonwealth Scientific and Industrial Research Organisation (CSIRO)
# ABN 41 687 119 230.
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(DATA61_BSD)
#
#

CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))


Server_CFILES := ${CURRENT_DIR}/server.c
Server_HFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/include/*.h))

CAMKES_FLAGS += --cpp-flag=-I${SOURCE_DIR}/include
