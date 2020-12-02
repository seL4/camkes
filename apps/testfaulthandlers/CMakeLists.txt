#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(testfaulthandlers C)

DeclareCAmkESComponent(Client SOURCES client.c INCLUDES .)
DeclareCAmkESComponent(Server SOURCES server.c INCLUDES .)

DeclareCAmkESRootserver(testfaulthandlers.camkes)
add_simulate_test([=[wait_for "FAULT HANDLER"]=])
