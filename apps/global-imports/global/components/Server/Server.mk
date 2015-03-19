Server_GLOBAL := 1

CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))

Server_CFILES := $(wildcard ${CURRENT_DIR}/src/*.c)
Server_HFILES := $(wildcard ${CURRENT_DIR}/include/*.h)

Server_EXPORT_HFILES := $(wildcard ${CURRENT_DIR}/../common_port_types/shared_int.h)
Server_HFILES += ${Server_EXPORT_HFILES}

include GetterIface/GetterIface.mk
Server_HFILES += ${GetterIface_EXPORT_HFILES}
