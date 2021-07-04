#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(swapcounter C)

set(CAmkESErrorHandlingMode Guards CACHE STRING "" FORCE)
set(CAmkESUnifiedThy ON CACHE BOOL "" FORCE)
set(CAmkESPruneGenerated ON CACHE BOOL "" FORCE)

DeclareCAmkESComponent(Client SOURCES client.c)
DeclareCAmkESComponent(Service SOURCES service.c)

DeclareCAmkESRootserver(swapcounter.camkes)
add_simulate_test([=[wait_for "done"]=])
