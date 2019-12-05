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

project(hierarchical-attributes C)

DeclareCAmkESComponent(Foo SOURCES components/Foo/src/main.c)
DeclareCAmkESComponent(Bar SOURCES components/Bar/src/main.c)
DeclareCAmkESComponent(Baz SOURCES components/Baz/src/main.c)
DeclareCAmkESComponent(Controller SOURCES components/Controller/src/main.c)

DeclareCAmkESRootserver(hierarchical-attributes.camkes)
add_simulate_test([=[wait_for "str: world"]=])
