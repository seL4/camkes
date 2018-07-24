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

project(terminal C)

ExternalProject_Add(termsize SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/tools" CMAKE_CACHE_ARGS "-DCMAKE_INSTALL_PREFIX:STRING=${CMAKE_CURRENT_BINARY_DIR}/termsize")

add_custom_command(OUTPUT include/terminal_terminal.h
    COMMAND termsize/bin/termsize include/terminal_terminal.h
    DEPENDS termsize
    USES_TERMINAL
)

add_custom_target(terminal_h DEPENDS include/terminal_terminal.h)

DeclareCAmkESComponent(Client SOURCES components/Client/src/client.c)
DeclareCAmkESComponent(Manager SOURCES components/Manager/src/display.c INCLUDES components/Manager/include include)
add_dependencies(CAmkESComponent_Manager terminal_h)

DeclareCAmkESRootserver(terminal.camkes)
