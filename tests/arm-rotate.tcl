#!/usr/bin/expect -f
# @TAG(NICTA_BSD)

source [file join [file dirname [info script]] procs.tcl]

set timeout 600

spawn make arm_rotate_defconfig
check_exit

source [file join [file dirname [info script]] build.tcl]

source [file join [file dirname [info script]] run-arm.tcl]
wait_for "Afterwards we have (ret)2, (in)2, (out)4, (inout)2"
