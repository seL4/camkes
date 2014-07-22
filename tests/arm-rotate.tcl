#!/usr/bin/expect -f
#
# Copyright 2014, NICTA
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(NICTA_BSD)
#

source [file join [file dirname [info script]] procs.tcl]

set timeout 300

spawn make arm_rotate_defconfig
check_exit

source [file join [file dirname [info script]] build.tcl]

source [file join [file dirname [info script]] run-arm.tcl]
wait_for "Afterwards we have (ret)2, (in)2, (out)4, (inout)2"
