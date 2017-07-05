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

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := alignment.camkes

Client_CFILES := ${SOURCE_DIR}/client.c $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/common/*.c))
Server_CFILES := ${SOURCE_DIR}/server.c $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/common/*.c))

Client_HFILES += $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/common/*.h))
Server_HFILES += $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/common/*.h))

Client_ASMFILES += $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/common/*.S))
Server_ASMFILES += $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/common/*.S))

include ${PWD}/tools/camkes/camkes.mk
