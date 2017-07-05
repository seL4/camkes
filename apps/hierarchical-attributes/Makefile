# @TAG(DATA61_BSD)
#

TARGETS := hierarchical-attributes.cdl
ADL := hierarchical-attributes.camkes

Foo_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Foo/src/*.c))
Bar_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Bar/src/*.c))
Baz_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Baz/src/*.c))
Controller_CFILES := $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Controller/src/*.c))

include ${PWD}/tools/camkes/camkes.mk
