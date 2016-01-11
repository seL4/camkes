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
ADL := aeroplage.camkes

KeyboardDriver_HFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/KeyboardDriver/*.h))
KeyboardDriver_CFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/KeyboardDriver/*.c))
KeyboardDriver_LIBS += ringbuffer sel4keyboard

Switch_HFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Switch/*.h))
Switch_CFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Switch/*.c))
Switch_LIBS += ringbuffer

MockLinux_HFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/MockLinux/*.h))
MockLinux_CFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/MockLinux/*.c))
MockLinux_LIBS += ringbuffer

VESADriver_HFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/VESADriver/*.h))
VESADriver_CFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/VESADriver/*.c))
VESADriver_LIBS += ringbuffer sel4bga

include ${PWD}/tools/camkes/camkes.mk
