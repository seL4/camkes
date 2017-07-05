#!/usr/bin/expect -f
# @TAG(DATA61_BSD)

# Inhibit concurrency.
set argv [list ];

source [file join [file dirname [info script]] procs.tcl]

set timeout 600

spawn make arm_terminal_defconfig
check_exit

source [file join [file dirname [info script]] build.tcl]
