# @TAG(DATA61_BSD)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := rumprun_ethernet.camkes
TEMPLATES += ../../projects/global-components/templates

PROJECT_BASE := $(PWD)
RUMPRUN_BASE_DIR := $(PWD)/libs/rumprun


all: default

include TimeServer/TimeServer.mk
include SerialServer/SerialServer.mk
include PCIConfigIO/PCIConfigIO.mk

include ${SOURCE_DIR}/components/rump_ether/rump_ether.mk
include ${SOURCE_DIR}/components/reverse_string/server.mk



include ${PWD}/tools/camkes/camkes.mk
