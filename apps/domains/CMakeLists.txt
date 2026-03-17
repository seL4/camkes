#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.16.0)

project(event C)

DeclareCAmkESComponent(Collector SOURCES components/Collector/src/collector.c)
DeclareCAmkESComponent(Emitter SOURCES components/Emitter/src/emitter.c)

DeclareCAmkESRootserver(domains.camkes)
add_simulate_test([=[wait_for "done emitting events"]=])
