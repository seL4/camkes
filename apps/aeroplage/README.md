<!--@TAG(NICTA_BSD)-->
# Aeroplage - a prototype of a multilevel terminal

This application implements a prototype of a previous multilevel terminal for seL4. It currently
runs on x86 in Qemu. To build it, you will need to apply the included patch to the CapDL
initialiser. This is due to a current lack of support for large device regions. After building the
application, you can run it with the following Qemu invocation:

    qemu-system-i386 -m 1024 -serial /dev/stdout -vga std -kernel images/kernel-ia32-pc99 \
      -initrd images/capdl-loader-experimental-image-ia32-pc99

When running it should show two panels of different colours. You can type to enter text into one, or
press Tab to change to the other.
