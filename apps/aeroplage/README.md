<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

# Aeroplage - a prototype of a multilevel terminal

This application implements a prototype of a previous multilevel terminal for seL4. It currently
runs on x86 in Qemu. After building the application, you can run it with the following Qemu invocation:

    qemu-system-i386 -m 1024 -serial stdio -vga std -kernel images/kernel-ia32-pc99 \
      -initrd images/capdl-loader-experimental-image-ia32-pc99

When running it should show two panels of different colours. You can type to enter text into one, or
press Tab to change to the other.
