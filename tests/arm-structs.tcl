#!/usr/bin/expect -f
# @TAG(DATA61_BSD)

source [file join [file dirname [info script]] procs.tcl]

set timeout 600

spawn make arm_structs_defconfig
check_exit

source [file join [file dirname [info script]] build.tcl]

source [file join [file dirname [info script]] run-arm.tcl]
wait_for "array_in_struct: array length: 4, first element 3"
