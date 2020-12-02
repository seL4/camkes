#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(mutex C)

DeclareCAmkESComponent(A SOURCES components/A/src/main.c)
DeclareCAmkESComponent(B SOURCES components/B/src/main.c)

CAmkESAddTemplatesPath(templates)
DeclareCAmkESConnector(seL4MyConnector FROM seL4MyConnector-from.c TO seL4MyConnector-to.c)
DeclareCAmkESRootserver(mutex.camkes)
add_simulate_test([=[wait_for "b: Exiting"]=])
