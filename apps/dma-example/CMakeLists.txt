#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
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
