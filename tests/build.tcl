# @TAG(DATA61_BSD)
#

# This fragment is expected to included by other tests.

# Take the level of parallelism from the first argument, if given.
set jobs [expr {[lindex $argv 0] ne "" ? [lindex $argv 0] : 1}];

spawn make silentoldconfig
check_exit

spawn make clean
check_exit

spawn make --jobs=$jobs
check_exit
