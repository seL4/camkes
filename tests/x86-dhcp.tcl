#!/usr/bin/expect -f
# @TAG(NICTA_BSD)

source [file join [file dirname [info script]] procs.tcl]

set timeout 600

spawn make x86_dhcp_defconfig
check_exit

source [file join [file dirname [info script]] build.tcl]

source [file join [file dirname [info script]] run-x86.tcl]
wait_for "a: Acquired IP 192.168.1.5"
