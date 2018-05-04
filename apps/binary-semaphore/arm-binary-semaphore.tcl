#!/usr/bin/expect -f
#
# Copyright 2017, Data61
# Commonwealth Scientific and Industrial Research Organisation (CSIRO)
# ABN 41 687 119 230.
#
# This software may be distributed and modified according to the terms of
# the GNU General Public License version 2. Note that NO WARRANTY is provided.
# See "LICENSE_GPLv2.txt" for details.
#
# @TAG(DATA61_GPL)
#

source [file join $::env(SCRIPT_DIR) procs.inc]

set timeout 600

spawn make arm_binary_semaphore_defconfig
check_exit

source [file join $::env(SCRIPT_DIR) build.inc]

source [file join $::env(SCRIPT_DIR) run-arm.inc]
wait_for "Echoing: 42 == 42"
