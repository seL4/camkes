#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(hierarchical-attributes C)

DeclareCAmkESComponent(Foo SOURCES components/Foo/src/main.c)
DeclareCAmkESComponent(Bar SOURCES components/Bar/src/main.c)
DeclareCAmkESComponent(Baz SOURCES components/Baz/src/main.c)
DeclareCAmkESComponent(Controller SOURCES components/Controller/src/main.c)

DeclareCAmkESRootserver(hierarchical-attributes.camkes)
add_simulate_test([=[wait_for "str: world"]=])
