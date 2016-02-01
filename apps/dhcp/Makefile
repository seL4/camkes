#
# Copyright 2016, NICTA
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(NICTA_BSD)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := $(notdir ${SOURCE_DIR}).camkes

Client_CFILES := src/client.c src/util.c
Client_HFILES := src/util.h

Server_CFILES := src/server.c src/util.c
Server_HFILES := src/util.h

include ${PWD}/tools/camkes/camkes.mk
