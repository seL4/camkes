#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(structs C)

DeclareCAmkESComponent(Client SOURCES components/Client/src/client.c)

DeclareCAmkESRootserver(structs.camkes)
add_simulate_test([=[wait_for "array_in_struct: array length: 4, first element 3"]=])
