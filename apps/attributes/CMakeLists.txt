#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(attributes C)

DeclareCAmkESComponent(foo SOURCES foo.c)
DeclareCAmkESComponent(bar SOURCES bar.c)
DeclareCAmkESComponent(baz)

DeclareCAmkESRootserver(attributes.camkes)
add_simulate_test([=[
    wait_for "a = 11, b = 1"
    wait_for "c = 5, d = 4"
]=])
