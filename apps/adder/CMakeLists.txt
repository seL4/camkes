#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(adder C)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/components/Adder)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/components/Client)

DeclareCAmkESRootserver(adder.camkes)
add_simulate_test([=[wait_for "client: result was 1270"]=])
