#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(filter C)

DeclareCAmkESComponent(Client SOURCES components/Client/src/client.c)
DeclareCAmkESComponent(Filter SOURCES components/Filter/src/main.c)
DeclareCAmkESComponent(Store SOURCES components/Store/src/main.c)

DeclareCAmkESRootserver(filter.camkes)
add_simulate_test([=[wait_for "received value \\\"\\\""]=])
