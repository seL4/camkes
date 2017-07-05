# @TAG(DATA61_BSD)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := rumprun_pthreads.camkes
TEMPLATES += ../../projects/global-components/templates

PROJECT_BASE := $(PWD)
RUMPRUN_BASE_DIR := $(PWD)/libs/rumprun


all: default

include TimeServer/TimeServer.mk
include SerialServer/SerialServer.mk

include ${SOURCE_DIR}/components/pthreads/pthreads.mk



include ${PWD}/tools/camkes/camkes.mk
