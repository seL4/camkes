#
# Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

includeGlobalComponents()

project(global_async C)
DeclareCAmkESComponent(
    Client
    SOURCES
    components/Client/src/client.c
    components/Client/src/client_events.c
)

DeclareCAmkESComponent(Sender SOURCES components/Sender/src/sender.c)

DeclareCAmkESRootserver(global_async.camkes)
add_simulate_test([=[wait_for "Got an event : Incoming data is OKVje138PB1J@cG?ObN2"]=])
