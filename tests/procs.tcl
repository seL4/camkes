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
