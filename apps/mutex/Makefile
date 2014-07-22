#
# Copyright 2014, NICTA
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(NICTA_BSD)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := mutex.camkes

A_CFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/A/src/*.c))

B_CFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/B/src/*.c))

# Note, A does not depend on libsel4sync because the mutex is hosted in B.
B_LIBS := sel4sync

# Subdirectory containing extra templates.
TEMPLATES := templates

include ${PWD}/tools/camkes/camkes.mk
