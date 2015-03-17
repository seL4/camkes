include Server.mk
include Printer.mk

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := global-imports.camkes

# Source and header files for a local component
Client_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Client/src/*.c))
Client_HFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Client/include/*.h))

include ${PWD}/tools/camkes/camkes.mk
