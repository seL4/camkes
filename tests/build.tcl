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

# Allow a --sequential flag that disables parallel compilation of muslc
set jobs [expr {[lindex $argv 0] eq "--sequential" ? "--jobs=1" : "--jobs"}];

spawn make silentoldconfig
check_exit

spawn make clean
check_exit

spawn make $jobs libmuslc
check_exit

spawn make
check_exit
