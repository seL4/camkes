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

include Server/Server.mk
include Printer/Printer.mk
include GetterIface/GetterIface.mk
include PrinterIface/PrinterIface.mk

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := global-imports.camkes

# Source and header files for a local component
Client_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Client/src/*.c))
Client_HFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Client/include/*.h))
Client_HFILES += ${GetterIface_EXPORT_HFILES} ${PrinterIface_EXPORT_HFILES} ${Server_EXPORT_HFILES}

include ${PWD}/tools/camkes/camkes.mk
