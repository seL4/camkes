#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(cs-nodonate C)

DeclareCAmkESComponent(Client SOURCES components/Client/src/client.c)
DeclareCAmkESComponent(Server SOURCES components/Server/src/server.c)
DeclareCAmkESRootserver(cs-nodonate.camkes)
add_simulate_test([=[wait_for "After the client"]=])
