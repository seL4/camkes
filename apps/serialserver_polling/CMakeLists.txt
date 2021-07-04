#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(serialserver_polling C)

set(CAmkESCPP ON CACHE BOOL "" FORCE)
includeGlobalComponents()
DeclareCAmkESComponent(Client SOURCES components/Client/src/polling-client.c)
DeclareCAmkESRootserver(serialserver_polling.camkes)
add_simulate_test([=[
    wait_for "pollcli: Hello Serial Server!"
    send "Hello world!\\r"
    wait_for "pollcli: Hello world!"
    ]=])
