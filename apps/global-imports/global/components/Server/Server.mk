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

Server_CFILES := $(wildcard ${CURRENT_DIR}/src/*.c)
Server_HFILES := $(wildcard ${CURRENT_DIR}/include/*.h)

Server_EXPORT_HFILES := $(wildcard ${CURRENT_DIR}/../common_port_types/shared_int.h)
Server_HFILES += ${Server_EXPORT_HFILES}

include GetterIface/GetterIface.mk
Server_HFILES += ${GetterIface_EXPORT_HFILES}
