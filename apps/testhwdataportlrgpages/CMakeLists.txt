#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(testhwdataportlrgpages C)

set(CAmkESLargeFramePromotion ON CACHE BOOL "" FORCE)
set(CAmkESCPP ON CACHE BOOL "" FORCE)

DeclareCAmkESComponent(Main SOURCES main.c)

DeclareCAmkESRootserver(testhwdataportlrgpages.camkes CPP_FLAGS -DSABRE)
add_simulate_test([=[wait_for "Hello, World!"]=])
