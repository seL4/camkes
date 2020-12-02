#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(Server C)

# Interface library for our dataport
add_library(ServerInterface INTERFACE)
target_include_directories(ServerInterface INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/../common_port_types")

DeclareCAmkESComponent(Server SOURCES src/main.c LIBS GetterIface ServerInterface)
