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

project(socket C)

# Each component having their own include directory with the same copy of socket.h
# in it should be fixed at some point
DeclareCAmkESComponent(Sender SOURCES components/Sender/src/sender.c INCLUDES components/Sender/include)
DeclareCAmkESComponent(Transport SOURCES components/Transport/src/transport.c INCLUDES components/Transport/include)
DeclareCAmkESComponent(Receiver SOURCES components/Receiver/src/receiver.c INCLUDES components/Receiver/include)

DeclareCAmkESRootserver(socket.camkes)
