#!/bin/sh
#
# Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

rm -rf test
mkdir -p test
(cd test && cmake -G Ninja $@ && ninja && ctest $VERBOSE)
