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

project(reversestring C)

set(CAmkESCPP ON CACHE BOOL "" FORCE)

DeclareCAmkESComponent(Client SOURCES src/client.c INCLUDES include)
DeclareCAmkESComponent(Server SOURCES src/server.c INCLUDES include)

DeclareCAmkESRootserver(reversestring.camkes CPP_INCLUDES include)
