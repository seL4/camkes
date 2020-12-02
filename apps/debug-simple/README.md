<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

This is an example of CAmkES RPC connection, using the CAmkES GDB debugger.

See [DEBUG.md](https://github.com/seL4/camkes-tool/blob/master/docs/DEBUG.md) for more information.
If this project is checked out using repo, a copy of these docs can be found in tools/camkes/docs/DEBUG.md

To run this app:
```bash
# From an empty directory
repo init -u https://github.com/seL4/camkes-manifest.git
# repo has been initialized in blah
repo sync
# Fetching projects: 100% (10/10), done.
make x86_debug_simple_defconfig
#
# configuration written to .config
#
make # -j 8
# [GEN_IMAGE] capdl-loader-experimental-image

qemu-system-i386 -nographic -m 512 -cpu Haswell \
    -kernel kernel-ia32-pc99 \
    -initrd capdl-loader-experimental-image-ia32-pc99 \
    -device isa-serial,chardev=ch0 \
    -device isa-serial,chardev=ch1 \
    -chardev file,path=/dev/tty,id=ch0 \
    -chardev socket,host=127.0.0.1,port=1234,id=ch1,server,wait
# QEMU waiting for connection on: disconnected:tcp:127.0.0.1:1234,server
# Run gdb in your top level project
gdb stage/x86/pc99/bin/client_group_bin
# Reading symbols from stage/x86/pc99/bin/client_group_bin...done.
(gdb) target remote:1234
# Remote debugging using :1234
# Remote debugging using :1234
# run () at somepath/camkes-gdb/apps/debug-simple/client.c:31
# 31	    camkes_software_breakpoint();
(gdb) c
# Continuing.

# Program received signal SIGTRAP, Trace/breakpoint trap.
# run () at somepath/camkes-gdb/apps/debug-simple/client.c:32
# 32	    j = a_echo_int(i);
(gdb) # You can now debug things
```