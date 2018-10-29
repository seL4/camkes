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

set x86_defconfig cakeml_hello_defconfig
set extra_cmake_args "-DCAKEMLDIR=/cakeml -DCAKEML_BIN=/cake-x64-64/cake"

set testscript {
	wait_for "Goodbye: bye"
}

source [file join $::env(SCRIPT_DIR) test.inc]
