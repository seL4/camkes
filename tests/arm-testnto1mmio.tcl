#!/usr/bin/expect -f
# @TAG(NICTA_BSD)

source [file join [file dirname [info script]] procs.tcl]

set timeout 600

spawn make arm_testnto1mmio_defconfig
check_exit

source [file join [file dirname [info script]] build.tcl]

source [file join [file dirname [info script]] run-arm.tcl]
wait_for "hello from drv1"
wait_for "hello from drv2"
