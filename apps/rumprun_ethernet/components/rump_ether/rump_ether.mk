# @TAG(DATA61_BSD)
#

CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))

include ${RUMPRUN_BASE_DIR}/platform/sel4/rumprunlibs.mk

cfiles := $(wildcard ${CURRENT_DIR}/tcp_server.c)
CAMKES_FLAGS += --cpp-flag=-I${RUMPRUN_BASE_DIR}/platform/sel4/camkes/ 


rumprun_ether_rumpbin := hello

hello: $(cfiles)
	echo ${CURRENT_DIR}
	$(RUMPRUN_CC) -I${CURRENT_DIR}/../../include $^ -o $@ -lpthread

