#
# Copyright 2014, NICTA
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(NICTA_BSD)
#

# This fragment is expected to included by other tests.

spawn qemu-system-i386 -nographic -kernel images/kernel-x86-pc99 -initrd images/capdl-loader-experimental-image-x86-pc99
