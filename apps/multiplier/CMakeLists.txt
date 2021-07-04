#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(multiplier C)

DeclareCAmkESComponent(Multiplier SOURCES components/Multiplier/src/main.c)
DeclareCAmkESComponent(Client SOURCES components/Client/src/client.c)

DeclareCAmkESRootserver(multiplier.camkes)
add_simulate_test([=[wait_for "client: other is {7, 8, }"]=])
