# @TAG(DATA61_BSD)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := $(notdir ${SOURCE_DIR}).camkes

Client_CFILES := src/client.c src/util.c
Client_HFILES := src/util.h

Server_CFILES := src/server.c src/util.c
Server_HFILES := src/util.h

include ${PWD}/tools/camkes/camkes.mk
