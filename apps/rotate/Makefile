# @TAG(DATA61_BSD)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := rotate.camkes

Client_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Client/src/*.c))

Client_HFILES := MyType.h
Server_HFILES := MyType.h

Server_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Server/src/*.c))

include ${PWD}/tools/camkes/camkes.mk
