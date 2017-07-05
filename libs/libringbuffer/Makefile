# @TAG(NICTA_BSD)
#

# seL4 build system support.

TARGETS := libringbuffer.a

# Source files required to build the target
CFILES := $(patsubst $(SOURCE_DIR)/%,%,$(wildcard $(SOURCE_DIR)/src/*.c))

# Header files/directories this library provides
HDRFILES := $(wildcard $(SOURCE_DIR)/include/*)

include $(SEL4_COMMON)/common.mk
