#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(reversestring C)

set(CAmkESCPP ON CACHE BOOL "" FORCE)

DeclareCAmkESComponent(Client SOURCES src/client.c INCLUDES include)
DeclareCAmkESComponent(Server SOURCES src/server.c INCLUDES include)

DeclareCAmkESRootserver(reversestring.camkes CPP_INCLUDES include)
add_simulate_test([=[wait_for "!dlroW ,olleH"]=])
