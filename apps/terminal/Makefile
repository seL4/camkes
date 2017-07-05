#
# Copyright 2017, Data61
# Commonwealth Scientific and Industrial Research Organisation (CSIRO)
# ABN 41 687 119 230.
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(DATA61_BSD)
#
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := $(notdir ${SOURCE_DIR}).camkes

PRIORITY_TARGETS = ${STAGE_DIR}/include/terminal_terminal.h

Client_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Client/src/*.c))

Manager_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Manager/src/*.c))
Manager_HFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Manager/include/*.h))

include ${PWD}/tools/camkes/camkes.mk

${STAGE_DIR}/tools:
	${Q}mkdir -p "${STAGE_DIR}/tools"

${STAGE_DIR}/tools/termsize: ${SOURCE_DIR}/tools/termsize.c \
                            |${STAGE_DIR}/tools
	@echo " [CC] $(notdir $@)"
	${Q}${HOSTCC} ${HOSTCFLAGS} "$^" -o "$@"

${STAGE_DIR}/include/terminal_terminal.h: ${STAGE_DIR}/tools/termsize
	@echo " [GEN] $(notdir $@)"
	${Q}$^ "$@"
