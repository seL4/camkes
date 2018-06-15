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

project(cakeml_hello C)

DeclareCAmkESComponent(Client
    SOURCES client.c
)

DeclareCAmkESComponent(Hello
    CAKEML_SOURCES componentScript.sml
    # Demonstrate that we can override the heap size
    CAKEML_HEAP_SIZE 51
)

DeclareCAmkESRootserver(cakeml_hello.camkes)
