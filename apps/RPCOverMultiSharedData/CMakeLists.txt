#
# Copyright 2020, Data61
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

includeGlobalComponents()
project(RPCOverMultiSharedData C)

DeclareCAmkESComponent(Adder SOURCES components/Adder/src/adder.c INCLUDES include)
DeclareCAmkESComponent(Client SOURCES components/Client/src/client.c INCLUDES include)

DeclareCAmkESRootserver(project.camkes)
add_simulate_test([=[wait_for "client: result was 1270"]=])
