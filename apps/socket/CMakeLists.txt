#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(socket C)

# Each component having their own include directory with the same copy of socket.h
# in it should be fixed at some point
DeclareCAmkESComponent(
    Sender
    SOURCES
    components/Sender/src/sender.c
    INCLUDES
    components/Sender/include
)
DeclareCAmkESComponent(
    Transport
    SOURCES
    components/Transport/src/transport.c
    INCLUDES
    components/Transport/include
)
DeclareCAmkESComponent(
    Receiver
    SOURCES
    components/Receiver/src/receiver.c
    INCLUDES
    components/Receiver/include
)

DeclareCAmkESRootserver(socket.camkes)
add_simulate_test([=[wait_for "receiver: Done."]=])
