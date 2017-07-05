#!/usr/bin/expect -f
# @TAG(DATA61_GPL)

source [file join [file dirname [info script]] procs.tcl]

set timeout 600

spawn make x86_binary_semaphore_defconfig
check_exit

source [file join [file dirname [info script]] build.tcl]

source [file join [file dirname [info script]] run-x86.tcl]
wait_for "Echoing: 42 == 42"
