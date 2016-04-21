#!/bin/bash
#
# Copyright 2016, NICTA
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(NICTA_BSD)
#

# Runs all tests, producing junit-compatible xml. This is intended to be run on
# a regression server. It attempts to retry hanging builds a given number of
# times before declaring them to have failed.

RETRIES=5
TIMEOUT=900 # 15 minutes

TIMEOUT_STATUS=124 # exit status indicating timeout

# Make a temporary file for storing compiler log
LOG=$(mktemp)
trap "rm $LOG" EXIT
echo "Outputing to $LOG"

echo "<testsuite>"

for t in $(ls tests); do
    if [ "$t" != "run-all.sh" -a "$t" != "run-all-xml.sh" ]; then

        file="tests/$t"
        if [ -x $file -a -f $file ]; then
            echo "<testcase classname='camkestest' name='$t'>"

            # Run the test, retrying if the test hangs
            TIMED_OUT=1
            STATUS=-1
            for i in $(seq 1 $RETRIES); do
                echo "Running $t...(attempt $i)"
                timeout $TIMEOUT ./tests/$t --sequential 2>&1 | tee $LOG
                STATUS=${PIPESTATUS[0]}
                if [ "$STATUS" = "$TIMEOUT_STATUS" ]; then
                    # test timed out
                    continue
                else
                    TIMED_OUT=0
                    break
                fi
            done

            if [ "$STATUS" != "0" ]; then
                if [ "$TIMED_OUT" != "0" ]; then
                    echo "<failure type='failure'>"
                else
                    echo "<failure type='timeout'>"
                fi

                # If the test failed, print the compiler output
                cat $LOG | sed -e "s/>/&gt;/g" | sed -e "s/</&lt;/g"
                echo "</failure>"
            fi

            echo "</testcase>"

        fi

    fi
done

echo "</testsuite>"
