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

project(mutex C)

DeclareCAmkESComponent(A SOURCES components/A/src/main.c)
DeclareCAmkESComponent(B SOURCES components/B/src/main.c)

CAmkESAddTemplatesPath(templates)
DeclareCAmkESConnector(seL4MyConnector FROM seL4MyConnector-from.c TO seL4MyConnector-to.c)
DeclareCAmkESRootserver(mutex.camkes)
