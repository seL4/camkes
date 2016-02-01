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

for i in `ls configs`; do
    echo -n "Testing $i ... "
    { make $i && make silentoldconfig && make clean && make ; } &>/dev/null
    if [ $? -eq 0 ]; then
        echo "[32mPassed[0m"
    else
        echo "[31mFailed[0m"
    fi
done
