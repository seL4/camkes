#!/usr/bin/expect -f
# @TAG(NICTA_BSD)

source [file join [file dirname [info script]] procs.tcl]

set timeout 600

spawn make arm_multiassembly_defconfig
check_exit

source [file join [file dirname [info script]] build.tcl]

source [file join [file dirname [info script]] run-arm.tcl]
wait_for "DLROW OLLEH"
