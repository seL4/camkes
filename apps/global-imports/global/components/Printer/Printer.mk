# @TAG(NICTA_BSD)
#

CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))

Printer_CFILES := $(wildcard ${CURRENT_DIR}/src/*.c)
Printer_HFILES := $(wildcard ${CURRENT_DIR}/include/*.h)

include PrinterIface/PrinterIface.mk
Printer_HFILES += ${PrinterIface_EXPORT_HFILES}
