#
# Copyright 2018, 2020, Data61
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

project(serialserver_polling C)

set(CAmkESCPP ON CACHE BOOL "" FORCE)
includeGlobalComponents()
DeclareCAmkESComponent(Client SOURCES components/Client/src/polling-client.c)
DeclareCAmkESRootserver(serialserver_polling.camkes)
add_simulate_test([=[wait_for "Hello Serial Server!"]=])
