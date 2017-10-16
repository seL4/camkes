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

project(aeroplage C)

set(KernelArch x86 CACHE STRING "" FORCE)

DeclareCAmkESComponent(KeyboardDriver SOURCES components/KeyboardDriver/driver.c LIBS ringbuffer sel4keyboard)
DeclareCAmkESComponent(MockLinux SOURCES components/MockLinux/mocklinux.c LIBS ringbuffer)
DeclareCAmkESComponent(Switch SOURCES components/Switch/switch.c LIBS ringbuffer)
DeclareCAmkESComponent(VESADriver SOURCES components/VESADriver/chars.c components/VESADriver/vesadriver.c LIBS ringbuffer sel4bga)

DeclareCAmkESRootserver(aeroplage.camkes)
