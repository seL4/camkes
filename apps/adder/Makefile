# @TAG(NICTA_BSD)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := adder.camkes

Adder_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Adder/src/*.c))
Adder_HFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Adder/include/*.h))

Client_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Client/src/*.c))
Client_HFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Client/include/*.h))

include ${PWD}/tools/camkes/camkes.mk
