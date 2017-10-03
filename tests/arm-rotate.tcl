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

source [file join [file dirname [info script]] procs.inc]

set timeout 600

spawn make arm_rotate_defconfig
check_exit

source [file join [file dirname [info script]] build.inc]

source [file join [file dirname [info script]] run-arm.inc]
wait_for "Afterwards we have (ret)2, (in)2, (out)4, (inout)2"
