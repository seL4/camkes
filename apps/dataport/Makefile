# @TAG(NICTA_BSD)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := dataport.camkes

DataportTest_CFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/DataportTest/src/*.c)) \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/DataportTest/src/plat/${PLAT}/*.c)) \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/DataportTest/src/arch/${ARCH}/*.c))

DataportTest_ASMFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/DataportTest/crt/arch-${ARCH}/crt0.S)) \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/DataportTest/src/*.S)) \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/DataportTest/src/arch/${ARCH}/*.S)) \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/DataportTest/src/plat/${PLAT}/*.S))

include ${PWD}/tools/camkes/camkes.mk
