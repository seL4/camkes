#
# Copyright 2020, Data61
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

project(mcs-scheduling C)

if(KernelArchARM)
    set(KernelArmExportPMUUser ON CACHE BOOL "" FORCE)
elseif(KernelArchX86)
    set(KernelExportPMCUser ON CACHE BOOL "" FORCE)
else()
    message("Unsupported platform.")
endif()

set(KernelDangerousCodeInjection ON CACHE BOOL "" FORCE)

if(SIMULATION)
    ApplyCommonSimulationSettings(${KernelArch})
endif()

DeclareCAmkESComponent(Task SOURCES components/Task/src/task.c LIBS sel4bench)
DeclareCAmkESComponent(Init SOURCES components/Init/src/init.c LIBS sel4bench)
DeclareCAmkESRootserver(mcs-scheduling.camkes)
# FIXME: Need additional configs for `sel4bench` to make this app compiled
# in simulate tests
# add_simulate_test([=[wait_for "[task_3] CPU utilization:"]=])
