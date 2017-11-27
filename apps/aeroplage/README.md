<!--
     Copyright 2017, Data61
     Commonwealth Scientific and Industrial Research Organisation (CSIRO)
     ABN 41 687 119 230.

     This software may be distributed and modified according to the terms of
     the BSD 2-Clause license. Note that NO WARRANTY is provided.
     See "LICENSE_BSD2.txt" for details.

     @TAG(DATA61_BSD)
-->
# Aeroplage - a prototype of a multilevel terminal

This application implements a prototype of a previous multilevel terminal for seL4. It currently
runs on x86 in Qemu. After building the application, you can run it with the following Qemu invocation:

    qemu-system-i386 -m 1024 -serial stdio -vga std -kernel images/kernel-ia32-pc99 \
      -initrd images/capdl-loader-experimental-image-ia32-pc99

When running it should show two panels of different colours. You can type to enter text into one, or
press Tab to change to the other.
