#!/bin/bash
# @TAG(NICTA_BSD)

for i in `ls configs`; do
    echo -n "Testing $i ... "
    { make $i && make silentoldconfig && make clean && make ; } &>/dev/null
    if [ $? -eq 0 ]; then
        echo "[32mPassed[0m"
    else
        echo "[31mFailed[0m"
    fi
done
