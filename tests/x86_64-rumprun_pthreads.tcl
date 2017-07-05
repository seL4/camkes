#!/usr/bin/expect -f
# @TAG(DATA61_BSD)

source [file join [file dirname [info script]] procs.tcl]

set timeout 600

spawn make x86_64_rumprun_pthreads_defconfig
check_exit

source [file join [file dirname [info script]] build.tcl]

source [file join [file dirname [info script]] run-x86_64.tcl]

wait_for "Waited and joined with 3 threads. Final value of count = 145. Done"
