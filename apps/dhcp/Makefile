#
# Copyright 2014, NICTA
#
# This software may be distributed and modified according to the terms of
# the GNU General Public License version 2. Note that NO WARRANTY is provided.
# See "LICENSE_GPLv2.txt" for details.
#
# @TAG(NICTA_GPL)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := $(notdir ${SOURCE_DIR}).camkes

Client_CFILES := src/client.c src/util.c
Client_HFILES := src/util.h

Server_CFILES := src/server.c src/util.c
Server_HFILES := src/util.h

include ${PWD}/tools/camkes/camkes.mk
