CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))

Server_CFILES := $(wildcard ${CURRENT_DIR}/src/*.c)
Server_HFILES := $(wildcard ${CURRENT_DIR}/include/*.h)

include GetterIface/GetterIface.mk
include SharedInt/SharedInt.mk
Server_HFILES += ${GetterIface_EXPORT_HFILES} ${SharedInt_EXPORT_HFILES}
