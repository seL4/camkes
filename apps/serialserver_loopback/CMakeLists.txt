#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(serialserver_loopback C)

set(CAmkESCPP ON CACHE BOOL "" FORCE)
includeGlobalComponents()
DeclareCAmkESComponent(Client 
    SOURCES components/Client/src/client.c
    LIBS virtqueue vswitch)
DeclareCAmkESRootserver(serialserver_loopback.camkes)
