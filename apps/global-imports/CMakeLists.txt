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

project(global-imports C)

# Include the 'global' component. This directory can be moved anywhere in the file system
# and only this import needs to be updated
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/global)

DeclareCAmkESComponent(Client SOURCES components/Client/src/main.c LIBS GetterIface PrinterIface ServerInterface)

DeclareCAmkESRootserver(global-imports.camkes)
add_simulate_test([=[
    wait_for "Hello, World!"
    wait_for "(4.000000, 2.000000)"
    wait_for "2"
]=])
