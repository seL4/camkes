#
# Copyright 2019, Data61
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

project(camkes-tests NONE)


enable_testing()

file(GLOB apps ${CMAKE_CURRENT_LIST_DIR}/../apps/*)

foreach(app IN LISTS apps)
	if(NOT IS_DIRECTORY ${app})
		continue()
	endif()
	file(GLOB tcls ${app}/*.tcl)
	foreach(tcl IN LISTS tcls)
		get_filename_component(name ${tcl} NAME_WE)
		add_test(NAME ${name} WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../../ COMMAND cmake -E env SCRIPT_DIR=${CMAKE_CURRENT_LIST_DIR} ${tcl})
	endforeach()

endforeach()
