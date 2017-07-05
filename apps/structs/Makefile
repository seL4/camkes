# @TAG(DATA61_BSD)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := structs.camkes

Client_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Client/src/*.c))
Client_HFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Client/include/*.h))

include ${PWD}/tools/camkes/camkes.mk
