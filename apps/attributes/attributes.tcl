#!/usr/bin/expect -f
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

set appname [file tail [file dirname [info script]]]

source [file join $::env(SCRIPT_DIR) procs.inc]

set arm_defconfig arm_attributes_defconfig
set x86_defconfig x86_attributes_defconfig
set riscv true

set testscript {
	wait_for "a = 11, b = 1"
	wait_for "c = 5, d = 4"
}

source [file join $::env(SCRIPT_DIR) test.inc]
