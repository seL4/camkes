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

project(rotate C)

DeclareCAmkESComponent(Client SOURCES components/Client/src/client.c INCLUDES .)
DeclareCAmkESComponent(Server SOURCES components/Server/src/server.c INCLUDES .)

DeclareCAmkESRootserver(rotate.camkes)
add_simulate_test([=[wait_for "Afterwards we have (ret)2, (in)2, (out)4, (inout)2"]=])
