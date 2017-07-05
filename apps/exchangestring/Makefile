# @TAG(NICTA_BSD)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := exchangestring.camkes

Server_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Server/src/*.c))

Client_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Client/src/*.c))

include ${PWD}/tools/camkes/camkes.mk
