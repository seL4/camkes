#!/usr/bin/expect -f
# @TAG(DATA61_GPL)

source [file join [file dirname [info script]] procs.tcl]

set timeout 600

spawn make arm_binary_semaphore_defconfig
check_exit

source [file join [file dirname [info script]] build.tcl]

source [file join [file dirname [info script]] run-arm.tcl]
wait_for "Echoing: 42 == 42"
