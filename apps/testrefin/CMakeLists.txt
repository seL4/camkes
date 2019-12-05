#
# Copyright 2018, Data61
# Commonwealth Scientific and Industrial Research Organisation (CSIRO)
# ABN 41 687 119 230.
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(DATA61_BSD)
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
