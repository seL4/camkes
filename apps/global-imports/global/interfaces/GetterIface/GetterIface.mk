CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))
GetterIface_EXPORT_HFILES := $(wildcard ${CURRENT_DIR}/../common_procedure_types/vector.h)
