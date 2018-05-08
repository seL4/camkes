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

source [file join $::env(SCRIPT_DIR) procs.inc]

set x86_64_defconfig x86_64_alignment_defconfig
set x86_defconfig x86_alignment_defconfig

set testscript {
	wait_for "All is well in the universe!"
}

source [file join $::env(SCRIPT_DIR) test.inc]
