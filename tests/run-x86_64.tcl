# @TAG(DATA61_BSD)
#

# This fragment is expected to included by other tests.

spawn qemu-system-x86_64 -nographic -cpu Haswell -enable-kvm -no-kvm-irqchip -kernel images/kernel-x86_64-pc99 -initrd images/capdl-loader-experimental-image-x86_64-pc99
