#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(cms-donate C)

DeclareCAmkESComponent(Client SOURCES components/Client/src/client.c)
DeclareCAmkESComponent(Intermediate SOURCES components/Intermediate/src/intermediate.c)
DeclareCAmkESComponent(Server SOURCES components/Server/src/server.c)
DeclareCAmkESRootserver(cms-donate.camkes)
add_simulate_test([=[
    wait_for "echo_parameter: 123 -> 123 (returned = 123)"
    wait_for "After the client"
]=])
