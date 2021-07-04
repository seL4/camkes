#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(lockserver C)

DeclareCAmkESComponent(Client SOURCES src/client.c)
DeclareCAmkESComponent(Server SOURCES src/server.c)

DeclareCAmkESRootserver(lockserver.camkes)
add_simulate_test([=[wait_for "c3: released"]=])
