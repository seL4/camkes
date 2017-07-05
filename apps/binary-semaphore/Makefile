#
# Copyright 2017, Data61
# Commonwealth Scientific and Industrial Research Organisation (CSIRO)
# ABN 41 687 119 230.
#
# This software may be distributed and modified according to the terms of
# the GNU General Public License version 2. Note that NO WARRANTY is provided.
# See "LICENSE_GPLv2.txt" for details.
#
# @TAG(DATA61_GPL)
#
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := binary-semaphore.camkes

Client_CFILES := ${SOURCE_DIR}/src/client.c
Server_CFILES := ${SOURCE_DIR}/src/server.c
Periodic_CFILES := ${SOURCE_DIR}/src/periodic.c

include ${PWD}/tools/camkes/camkes.mk
