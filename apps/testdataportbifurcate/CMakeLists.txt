#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(testdataportbifurcate C)

DeclareCAmkESComponent(Foo SOURCES foo.c)

DeclareCAmkESRootserver(testdataportbifurcate.camkes)
add_simulate_test([=[wait_for "All OK"]=])
