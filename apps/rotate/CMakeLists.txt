#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(rotate C)

DeclareCAmkESComponent(Client SOURCES components/Client/src/client.c INCLUDES .)
DeclareCAmkESComponent(Server SOURCES components/Server/src/server.c INCLUDES .)

DeclareCAmkESRootserver(rotate.camkes)
add_simulate_test([=[wait_for "Afterwards we have (ret)2, (in)2, (out)4, (inout)2"]=])
