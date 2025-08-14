#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.16.0)

project(testhardwareinterrupt C)

DeclareCAmkESComponent(Software SOURCES C.c)

DeclareCAmkESRootserver(testhardwareinterrupt.camkes)
