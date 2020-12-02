#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(testcamkes438 C)

DeclareCAmkESComponent(Foo SOURCES foo.c)
DeclareCAmkESComponent(Bar SOURCES bar.c)

DeclareCAmkESRootserver(testcamkes438.camkes)
add_simulate_test([=[wait_for "All OK"]=])
