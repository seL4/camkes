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

project(dma-example C)

DeclareCAmkESComponent(Client SOURCES client.c)
DeclareCAmkESComponent(Server SOURCES server.c)

# This needs large frame promotion to run in a reasonable amount of time
set(CAmkESDMALargeFramePromotion ON CACHE BOOL "" FORCE)

DeclareCAmkESRootserver(dma-example.camkes)
add_simulate_test([=[
    wait_for "Allocating 4MB..."
    wait_for "Succeeded"
    wait_for "Done."
]=])
