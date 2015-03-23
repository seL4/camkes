#
# Copyright 2014, NICTA
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(NICTA_BSD)
#

export PYTHONPATH:=${PYTHONPATH}:$(abspath tools/python-capdl)
export PATH:=${PATH}:$(abspath tools/camkes)

lib-dirs:=libs

# Isabelle theory pre-processor.
export TPP:=$(abspath tools/camkes/tools/tpp)

# Build the loader image, rather than the default (app-images) because the
# loader image actually ends up containing the component images.
all: capdl-loader-experimental-image

-include Makefile.local

# Strip the quotes from the string CONFIG_CAMKES_IMPORT_PATH.
CAMKES_IMPORT_PATH=$(patsubst %",%,$(patsubst "%,%,${CONFIG_CAMKES_IMPORT_PATH}))
#")") Help syntax-highlighting editors.

export MAKEFLAGS += $(foreach p, ${CAMKES_IMPORT_PATH}, --include-dir=${p})

include tools/common/project.mk

capdl-loader-experimental: $(filter-out capdl-loader-experimental,$(apps)) parse-capDL ${STAGE_BASE}/cpio-strip/cpio-strip
export CAPDL_SPEC:=$(foreach v,$(filter-out capdl-loader-experimental,${apps}),${BUILD_BASE}/${v}/${v}.cdl)

export PATH:=${PATH}:${STAGE_BASE}/parse-capDL
PHONY += parse-capDL
parse-capDL: ${STAGE_BASE}/parse-capDL/parse-capDL
${STAGE_BASE}/parse-capDL/parse-capDL:
	@echo "[$(notdir $@)] building..."
	$(Q)mkdir -p "${STAGE_BASE}"
	$(Q)cp -pur tools/capDL $(dir $@)
	$(Q)$(MAKE) --no-print-directory --directory=$(dir $@) 2>&1 \
        | while read line; do echo " $$line"; done; \
        exit $${PIPESTATUS[0]}
	@echo "[$(notdir $@)] done."

export PATH:=${PATH}:${STAGE_BASE}/cpio-strip
${STAGE_BASE}/cpio-strip/cpio-strip:
	@echo "[$(notdir $@)] building..."
	$(Q)mkdir -p "$(dir $@)"
	$(Q)cp -pu tools/common/cpio-strip.c $(dir $@)
	$(Q)cp -pu tools/common/Makefile.cpio_strip $(dir $@)
	$(Q)Q=${Q} CC=gcc $(MAKE) --makefile=Makefile.cpio_strip --no-print-directory \
      --directory=$(dir $@) 2>&1 \
      | while read line; do echo " $$line"; done; \
      exit $${PIPESTATUS[0]}
	@echo "[$(notdir $@)] done."

# Fail a default `make` if the user has selected multiple apps.
ifeq (${MAKECMDGOALS},)
  ifneq ($(words $(filter-out capdl-loader-experimental,${apps})),1)
    $(error Multiple CAmkES applications selected. Only a single application can be built at once)
  endif
endif

ifeq (${CONFIG_CAMKES_PRUNE_GENERATED},y)
${apps}: prune
endif
export PATH:=${STAGE_BASE}/pruner:${PATH}
PHONY += prune
prune: ${STAGE_BASE}/pruner/prune
CONFIG_CAMKES_LLVM_PATH:=$(CONFIG_CAMKES_LLVM_PATH:"%"=%)
ifeq (${CONFIG_CAMKES_LLVM_PATH},)
${STAGE_BASE}/pruner/prune: export CFLAGS=
else
  export PATH := ${CONFIG_CAMKES_LLVM_PATH}/bin:${PATH}
${STAGE_BASE}/pruner/prune: export CFLAGS=-I${CONFIG_CAMKES_LLVM_PATH}/include -L${CONFIG_CAMKES_LLVM_PATH}/lib
endif
${STAGE_BASE}/pruner/prune:
	@echo "[$(notdir $@)] building..."
	$(Q)mkdir -p "${STAGE_BASE}"
	$(Q)cp -pur tools/pruner $(dir $@)
	$(Q)CC=${HOSTCC} $(MAKE) V=$V --no-print-directory --directory=$(dir $@) 2>&1 \
        | while read line; do echo " $$line"; done; \
        exit $${PIPESTATUS[0]}
	@echo "[$(notdir $@)] done."

.PHONY: tags
tags:
	@find . \( -name "*.h" -o -name "*.c" -o -name "*.py" \) > list.txt
	@ctags-exuberant -L list.txt
	@rm list.txt
