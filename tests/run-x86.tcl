# @TAG(NICTA_BSD)
#

# This fragment is expected to included by other tests.

spawn qemu-system-i386 -nographic -cpu Haswell -enable-kvm -no-kvm-irqchip -kernel images/kernel-ia32-pc99 -initrd images/capdl-loader-experimental-image-ia32-pc99
