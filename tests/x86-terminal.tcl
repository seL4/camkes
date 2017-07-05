#!/usr/bin/expect -f
# @TAG(NICTA_BSD)

# Inhibit concurrency.
set argv [list ];

source [file join [file dirname [info script]] procs.tcl]

set timeout 600

spawn make x86_terminal_defconfig
check_exit

source [file join [file dirname [info script]] build.tcl]
