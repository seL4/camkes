#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(ComponentAdder C)

DeclareCAmkESComponent(Adder
    SOURCES src/adder.c
    INCLUDES include
)
