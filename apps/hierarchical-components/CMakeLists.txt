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

project(hierarchical-components C)

DeclareCAmkESComponent(Client SOURCES components/Client/src/main.c)
DeclareCAmkESComponent(Server SOURCES components/Server/src/main.c)
DeclareCAmkESComponent(Reverse SOURCES components/Reverse/src/main.c)
DeclareCAmkESComponent(UpperCase SOURCES components/UpperCase/src/main.c)
DeclareCAmkESComponent(Append SOURCES components/Append/src/main.c)
DeclareCAmkESComponent(Pipeline SOURCES components/Pipeline/src/main.c)
DeclareCAmkESComponent(SubPipeline)

DeclareCAmkESRootserver(hierarchical-components.camkes)
