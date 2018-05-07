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

# This file is supposed to be included from a CAmkES test that has declared the following:
# arm_defconfig: to build and run a binary on sabre
# x86_defconfig: to build and run a binary on ia32
# x86_64_defconfig: to build and run a binary on x86_64
# testscript: series of expect sequences that is run once the qemu process has started.
# setting override_timeout will override the default 600s timeout from being set.

if {[info exists override_timeout]} {set timeout $override_timeout} else {set timeout 600}

if {[info exists arm_defconfig]} {
	spawn make $arm_defconfig
	check_exit

	source [file join $::env(SCRIPT_DIR) build.inc]

	source [file join $::env(SCRIPT_DIR) run-arm.inc]

	eval $testscript
}

if {[info exists x86_defconfig]} {
	spawn make $x86_defconfig
	check_exit

	source [file join $::env(SCRIPT_DIR) build.inc]

	source [file join $::env(SCRIPT_DIR) run-x86.inc]

	eval $testscript
}

if {[info exists x86_64_defconfig]} {
	spawn make $x86_64_defconfig
	check_exit

	source [file join $::env(SCRIPT_DIR) build.inc]

	source [file join $::env(SCRIPT_DIR) run-x86_64.inc]

	eval $testscript
}
