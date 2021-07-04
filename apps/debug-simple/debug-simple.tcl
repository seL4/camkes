#!/usr/bin/expect -f
#
# Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

set appname [file tail [file dirname [info script]]]

source [file join $::env(SCRIPT_DIR) procs.inc]

set x86_defconfig x86_debug_simple_defconfig
set binary_location client_group_bin
set capdl_image_name capdl-loader-image-ia32-pc99
set testscript {
	spawn qemu-system-i386 -nographic -cpu Haswell -kernel images/kernel-ia32-pc99 -initrd images/$capdl_image_name -device isa-serial,chardev=ch0     -device isa-serial,chardev=ch1     -chardev file,path=/dev/tty,id=ch0     -chardev socket,host=127.0.0.1,port=1234,id=ch1,server,wait
	set qemuID $spawn_id

	wait_for "connection on: disconnected:tcp:127.0.0.1:1234,server"

	spawn gdb $binary_location
	set gdbID $spawn_id

	wait_for "(gdb)"

	# Connect to remote
	send "target remote:1234\r"
	wait_for "camkes_software_breakpoint();"

	# Test registers
	send "info registers\r"
	wait_for "esp"
	wait_for "_camkes_stack_client_0_control"

	# Test printing local variables
	send "p shello\r"
	wait_for "\"hello world\""

	send "p smore\r"
	wait_for "\"a longer string that will overflow the message registers on ARM\""

	send "p i\r"
	wait_for "42"

	send "p f\r"
	wait_for "273421\.438"

	send "p d\r"
	wait_for "273421\.42739999999"

	# Continue to go to next instruction
	send "continue \r"
	wait_for "j = a_echo_int\(i\);"

	# Test next command
	send "next \r"
	wait_for "printf\(\"echo_int: %d -> %d"

	send "p j\r"
	wait_for "42"

	# Test break points
	# Soft break
	send "break client.c:35\r"
	wait_for "Breakpoint 1 at"
	wait_for "line 35"

	send "c\r"
	wait_for "Breakpoint 1"
	wait_for "g = a_echo_float\(f\);"

	# Hbreak
	send "hbreak client.c:38\r"
	wait_for "Hardware assisted breakpoint 2 at"
	wait_for "line 38"

	send "c\r"
	wait_for "Breakpoint 2"
	wait_for "e = a_echo_double\(d\);"

	# test secondary camkes_software_breakpoint's
	send "c\r"
	wait_for "Program received signal SIGTRAP,"
	wait_for "j = a_echo_mix\(d\);"

	# test step
	send "s\r"
	wait_for "a_echo_mix \(d=273421.42739999999\)"

	# test watch
	send "watch global_number\r"
	wait_for "Hardware watchpoint 3: global_number"

	# Wait for variable to change
	send "c \r"
	wait_for "Hardware watchpoint 3: global_number"
	wait_for "Old value = 34"
	wait_for "New value = 50"
	wait_for "s = a_echo_string\(smore\);"

	# finish
	send "c\r"

	expect {
	    -i $qemuID
	    timeout {
	        exit 1
	    }
	    "After the client"
	}


}

source [file join $::env(SCRIPT_DIR) test.inc]
