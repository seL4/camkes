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
