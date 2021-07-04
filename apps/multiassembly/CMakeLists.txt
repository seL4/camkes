#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(multiassembly C)

# The multiassembly.camkes makes use of forward references, so force them to be on
set(CAmkESAllowForwardReferences ON CACHE BOOL "" FORCE)

DeclareCAmkESComponent(Client SOURCES components/Client/src/main.c)
DeclareCAmkESComponent(Server SOURCES components/Server/src/main.c)
DeclareCAmkESComponent(Reverse SOURCES components/Reverse/src/main.c)
DeclareCAmkESComponent(UpperCase SOURCES components/UpperCase/src/main.c)
DeclareCAmkESComponent(Append SOURCES components/Append/src/main.c)

DeclareCAmkESRootserver(multiassembly.camkes)
add_simulate_test([=[wait_for "DLROW OLLEH"]=])
