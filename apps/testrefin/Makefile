#
# Copyright 2015, NICTA
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(NICTA_BSD)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := $(notdir ${SOURCE_DIR}).camkes

Client_CFILES := client.c
Client_HFILES := my_struct.h
Server_CFILES := server.c
Server_HFILES := my_struct.h

include ${PWD}/tools/camkes/camkes.mk
