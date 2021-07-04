#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(serialserver_interrupt C)

set(CAmkESCPP ON CACHE BOOL "" FORCE)
includeGlobalComponents()
DeclareCAmkESComponent(Client SOURCES components/Client/src/interrupt-client.c)
DeclareCAmkESRootserver(serialserver_interrupt.camkes)
add_simulate_test([=[
    wait_for "interruptcli: Hello Serial Server!"
    send "Hello world!\\r"
    wait_for "interruptcli: Hello world!"
    ]=])
