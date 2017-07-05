# @TAG(DATA61_BSD)
#

CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))


Server_CFILES := ${CURRENT_DIR}/server.c
Server_HFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/include/*.h))

CAMKES_FLAGS += --cpp-flag=-I${SOURCE_DIR}/include
