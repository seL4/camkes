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

set arm_defconfig arm_rotate_defconfig
set x86_defconfig x86_rotate_defconfig

set testscript {
	wait_for "Afterwards we have (ret)2, (in)2, (out)4, (inout)2"
}

source [file join $::env(SCRIPT_DIR) test.inc]
