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

project(alignment C)

if (NOT KernelSel4ArchIA32)
    message(FATAL_ERROR "alignment application only supported on ia32")
endif()

DeclareCAmkESComponent(Client SOURCES client.c common/common.S INCLUDES common)
DeclareCAmkESComponent(Server SOURCES server.c common/common.S INCLUDES common)

DeclareCAmkESRootserver(alignment.camkes)
