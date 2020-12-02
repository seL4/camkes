#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(dataport C)

DeclareCAmkESComponent(DataportTest SOURCES components/DataportTest/src/client.c)

DeclareCAmkESRootserver(dataport.camkes)
add_simulate_test([=[wait_for "comp2 read hello world"]=])
