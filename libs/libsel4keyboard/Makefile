# @TAG(DATA61_BSD)
#

# Targets
TARGETS := $(notdir ${SOURCE_DIR}).a

# Source files required to build the target
CFILES := $(patsubst $(SOURCE_DIR)/%,%,$(wildcard ${SOURCE_DIR}/src/*.c))
CFILES += $(patsubst $(SOURCE_DIR)/%,%,$(wildcard ${SOURCE_DIR}/src/arch-$(ARCH)/*.c))

# Header files/directories this library provides
HDRFILES := \
	$(wildcard ${SOURCE_DIR}/include/*) \
	$(wildcard ${SOURCE_DIR}/arch_include/$(ARCH)/*)

include $(SEL4_COMMON)/common.mk
