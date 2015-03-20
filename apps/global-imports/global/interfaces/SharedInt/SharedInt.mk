CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))
SharedInt_EXPORT_HFILES := $(wildcard ${CURRENT_DIR}/shared_int.h)
