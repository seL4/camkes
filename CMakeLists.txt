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

cmake_minimum_required(VERSION 3.8.2)
include(settings.cmake)
project(camkes C CXX ASM)

find_package(camkes-tool REQUIRED)
find_package(global-components REQUIRED)
find_package(sel4_projects_libs REQUIRED)

# Set some options we know we need here. Applications can override them
set(CapDLLoaderMaxObjects 20000 CACHE STRING "")
set(KernelRootCNodeSizeBits 17 CACHE STRING "")
if(KernelArchARM)
    ApplyData61ElfLoaderSettings(${KernelPlatform} ${KernelSel4Arch})
endif()
camkes_tool_setup_camkes_build_environment()

sel4_projects_libs_import_libraries()

function(includeGlobalComponents)
    global_components_import_project()
endfunction()

enable_testing()
macro(add_simulate_test test_script)
	set(TEST_SCRIPT ${test_script})
	configure_file(${CMAKE_SOURCE_DIR}/tests/test_script.tcl.in ${CMAKE_BINARY_DIR}/test.tcl @ONLY)
	add_test(${CMAKE_PROJECT_NAME} expect -f ${CMAKE_BINARY_DIR}/test.tcl)
endmacro()

# We only support one application being built at a time
include(apps/${CAMKES_APP}/CMakeLists.txt)

# Should be done adding targets, can now generate the root server and the global configuration
GenerateCAmkESRootserver()
include(simulation)
if(SIMULATION)
    GenerateSimulateScript()
endif()
