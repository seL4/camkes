#
# Copyright 2017, Data61
# Commonwealth Scientific and Industrial Research Organisation (CSIRO)
# ABN 41 687 119 230.
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(DATA61_BSD)
#
#

CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))

include ${RUMPRUN_BASE_DIR}/platform/sel4/rumprunlibs.mk

CAMKES_FLAGS += --cpp-flag=-I${RUMPRUN_BASE_DIR}/platform/sel4/camkes/ 

# define path to the cargo project
RUST_SOURCE_DIR := ${CURRENT_DIR}/rustest/

rumprun_rust_rumpbin := hellorust

hellorust: $(RUST_SOURCE_DIR)/src/main.rs
	cd $(RUST_SOURCE_DIR) &&	cargo build --target=x86_64-rumprun-netbsd
	cp $(RUST_SOURCE_DIR)/target/x86_64-rumprun-netbsd/debug/rustest $(BUILD_DIR)/$@
