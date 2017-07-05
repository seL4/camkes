# @TAG(DATA61_BSD)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := reversestring.camkes

Client_CFILES := ${SOURCE_DIR}/src/client.c
Client_HFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/include/*.h))

Server_CFILES := ${SOURCE_DIR}/src/server.c
Server_HFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/include/*.h))

CAMKES_FLAGS += --cpp-flag=-I${SOURCE_DIR}/include

include ${PWD}/tools/camkes/camkes.mk
