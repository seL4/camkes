# @TAG(NICTA_BSD)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := socket.camkes

Sender_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Sender/src/*.c))
Sender_HFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Sender/include/*.h))

Transport_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Transport/src/*.c))
Transport_HFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Transport/include/*.h))

Receiver_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Receiver/src/*.c))
Receiver_HFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Receiver/include/*.h))

Sender_LIBS := c sel4sync
Transport_LIBS := c sel4sync
Receiver_LIBS := c sel4sync

include ${PWD}/tools/camkes/camkes.mk
