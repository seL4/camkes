#
# Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

includeGlobalComponents()
project(RPCOverMultiSharedData C)

DeclareCAmkESComponent(Adder SOURCES components/Adder/src/adder.c INCLUDES include)
DeclareCAmkESComponent(Client SOURCES components/Client/src/client.c INCLUDES include)

DeclareCAmkESRootserver(project.camkes)
add_simulate_test([=[wait_for "client: result was 1270"]=])
