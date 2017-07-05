# @TAG(DATA61_BSD)
#

CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))

include ${RUMPRUN_BASE_DIR}/platform/sel4/rumprunlibs.mk

HELLO_RUMP_CFILES := $(wildcard ${CURRENT_DIR}/pthreads.c)
CAMKES_FLAGS += --cpp-flag=-I${RUMPRUN_BASE_DIR}/platform/sel4/camkes/ 


rumprun_pthreads_rumpbin := hello

hello: $(HELLO_RUMP_CFILES)
	echo ${CURRENT_DIR}
	$(RUMPRUN_CC) $^ -o $@ -lpthread

