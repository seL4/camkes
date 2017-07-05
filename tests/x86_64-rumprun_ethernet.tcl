#!/usr/bin/expect -f
# @TAG(DATA61_BSD)

source [file join [file dirname [info script]] procs.tcl]

set timeout 600

spawn make x86_64_rumprun_ethernet_defconfig
check_exit

source [file join [file dirname [info script]] build.tcl]

source [file join [file dirname [info script]] run-x86_64.tcl]

wait_for "!dlroW ,olleH"
wait_for "Server is listening on 6666"
