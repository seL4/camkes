#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(testcontrolname C)

DeclareCAmkESComponent(Client SOURCES components/Client/src/client.c)
DeclareCAmkESComponent(Echo SOURCES components/Echo/src/echo.c)

DeclareCAmkESRootserver(testcontrolname.camkes)
add_simulate_test([=[wait_for "After the client"]=])
