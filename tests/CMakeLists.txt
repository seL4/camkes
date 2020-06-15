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

set(test_platforms sabre_sim ia32_sim spike64_sim)

set(sabre_sim_cmake "-DPLATFORM=sabre -DSIMULATION=ON -DCAmkESCapDLStaticAlloc=TRUE")
set(ia32_sim_cmake "-DPLATFORM=ia32 -DSIMULATION=ON")
set(spike64_sim_cmake "-DPLATFORM=spike -DRISCV64=ON -DSIMULATION=ON")
set(x86_64_sim_cmake "-DPLATFORM=x86_64 -DSIMULATION=ON")

file(GLOB apps ${CMAKE_CURRENT_LIST_DIR}/../apps/*)

macro(add_test_variant app_name test_platform test_variant)
    if(NOT "${test_variant}" STREQUAL "")
        set(test_name ${app_name}-${test_platform}-${test_variant})
    else()
        set(test_name ${app_name}-${test_platform})
    endif()
    add_test(
        ${test_name}
        ${CMAKE_CURRENT_LIST_DIR}/test_launcher.sh
        ${${test_platform}_cmake}
        ${${test_variant}_cmake}
        -DCAMKES_APP=${app_name}
        -C
        ${CMAKE_CURRENT_LIST_DIR}/../settings.cmake
        ${CMAKE_CURRENT_LIST_DIR}/../
    )

endmacro()

foreach(
    app
    IN
    ITEMS
    aeroplage
    alignment
    keyboard
    pit
    serialserver_polling
    serialserver_interrupt
    testhwdataportlrgpages
    timeserver
    vgatest
)
    add_test_variant(${app} ia32_sim "")
    list(APPEND exclude_apps ${app})
endforeach()

add_test_variant(alignment x86_64_sim "")

set(largeframe_cmake "-DCAmkESLargeFramePromotion=ON")
add_test_variant(dma-example ia32_sim largeframe)
add_test_variant(dma-example sabre_sim largeframe)
add_test_variant(dma-example spike64_sim largeframe)

set(cakeml_cmake "-DCAKEMLDIR=/cakeml -DCAKEML_BIN=/cake-x64-64/cake")
add_test_variant(cakeml_hello x86_64_sim cakeml)
add_test_variant(cakeml_tipc x86_64_sim cakeml)

foreach(app IN ITEMS fdtgen epit swapcounter testhwdataportlrgpages testnto1mmio uart_cogent)
    add_test_variant(${app} sabre_sim "")
    list(APPEND exclude_apps ${app})
endforeach()

list(
    APPEND
        exclude_apps
        cakeml_hello
        cakeml_regex
        cakeml_tipc
        debug-simple
        hellorust
        uart
        serialserver_loopback
        rumprun_rust
        rumprun_pthreads
        rumprun_hello
        rumprun_ethernet
        picoserver
        picotcp_tcp_echo
)

foreach(app IN LISTS apps)
    if(NOT IS_DIRECTORY ${app})
        continue()
    endif()
    get_filename_component(app ${app} NAME_WE)
    if(app IN_LIST exclude_apps)
        continue()
    endif()
    foreach(test_platform IN LISTS test_platforms)
        add_test_variant(${app} ${test_platform} "")
    endforeach()

endforeach()
