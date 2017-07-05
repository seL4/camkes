# @TAG(DATA61_BSD)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := alignment.camkes

Client_CFILES := ${SOURCE_DIR}/client.c $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/common/*.c))
Server_CFILES := ${SOURCE_DIR}/server.c $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/common/*.c))

Client_HFILES += $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/common/*.h))
Server_HFILES += $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/common/*.h))

Client_ASMFILES += $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/common/*.S))
Server_ASMFILES += $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/common/*.S))

include ${PWD}/tools/camkes/camkes.mk
