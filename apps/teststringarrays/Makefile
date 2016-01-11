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

A_HFILES := heap_check.h 
A_CFILES := A.c
B_CFILES := B.c
C_HFILES := heap_check.h 
C_CFILES := C.c

include ${PWD}/tools/camkes/camkes.mk
