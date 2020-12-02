#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(testrefin C)

DeclareCAmkESComponent(Client SOURCES client.c INCLUDES .)
DeclareCAmkESComponent(Server SOURCES server.c INCLUDES .)

DeclareCAmkESRootserver(testrefin.camkes)
add_simulate_test([=[
    wait_for "client: result was 42"
    wait_for "client: result was b = {0..99}"
]=])
