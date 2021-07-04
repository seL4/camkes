#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(testsyscalls C)

DeclareCAmkESComponent(Client SOURCES client.c)
DeclareCAmkESComponent(Server SOURCES server.c)

DeclareCAmkESRootserver(testsyscalls.camkes)
add_simulate_test([=[wait_for "All OK"]=])
