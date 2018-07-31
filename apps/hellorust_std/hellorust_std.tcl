#!/usr/bin/expect -f
#
# Copyright 2018, Data61
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

set appname hellorust_std
set x86_64_defconfig kbuildnotsupported

set testscript {
	wait_for "Hello, world!!"
}

source [file join $::env(SCRIPT_DIR) test.inc]
