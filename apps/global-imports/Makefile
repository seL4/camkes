TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := global-imports.camkes

# Source and header files for a local component
Client_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Client/src/*.c))
Client_HFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Client/include/*.h))

# List of components to be included from some external location.
# The compiler will search for a Makefile in the Server and Printer
# subdirectory of some global include directory.
GLOBAL_INCLUDES += Server Printer

include ${PWD}/tools/camkes/camkes.mk
