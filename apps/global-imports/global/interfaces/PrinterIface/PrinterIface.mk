# @TAG(DATA61_BSD)
#

CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))
PrinterIface_EXPORT_HFILES := $(wildcard ${CURRENT_DIR}/../common_procedure_types/vec.h)
