#
# Copyright 2016, NICTA
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(NICTA_BSD)
#

# This fragment is expected to included by other tests.

proc check_exit {} {
    expect eof
    catch wait result
    set status [lindex $result 3]
    if { $status != 0 } {
        exit $status
    }
}

proc wait_for { t } {
    expect {
        "$t" {
        }
        timeout {
            exit 1
        }
    }
}
