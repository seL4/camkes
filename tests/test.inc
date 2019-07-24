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

# This file is supposed to be included from a CAmkES test that has declared the following:
# arm_defconfig: to build and run a binary on sabre
# x86_defconfig: to build and run a binary on ia32
# x86_64_defconfig: to build and run a binary on x86_64
# testscript: series of expect sequences that is run once the qemu process has started.
# appname: name of folder containing app.  Used to init CMake
# extra_cmake_args: To add extra arguments onto a CMake init string.  PLATFORM, CAMKES_APP and TOOLCHAIN
#   settings are inferred from other settings.
# setting override_timeout will override the default 600s timeout from being set.

if {[info exists override_timeout]} {set timeout $override_timeout} else {set timeout 600}

if {![info exists extra_cmake_args]} {
    set extra_cmake_args ""
}

if {[info exists arm_defconfig]} {
    set cmake_props [concat -DARM=TRUE -DPLATFORM=sabre -DCAMKES_APP=$appname $extra_cmake_args]
    source [file join $::env(SCRIPT_DIR) build-cmake.inc]
    source [file join $::env(SCRIPT_DIR) run-cmake.inc]
    eval $testscript
    cd ../
}
# Also test capDL static allocation for all apps (on ARM)
if {[info exists arm_defconfig]} {
    set cmake_props [concat -DARM=TRUE -DPLATFORM=sabre -DCAMKES_APP=$appname -DCAmkESCapDLStaticAlloc=TRUE $extra_cmake_args]
    source [file join $::env(SCRIPT_DIR) build-cmake.inc]
    source [file join $::env(SCRIPT_DIR) run-cmake.inc]
    eval $testscript
    cd ../
}
if {[info exists x86_defconfig]} {
    set cmake_props [concat -DPLATFORM=ia32 -DCAMKES_APP=$appname $extra_cmake_args]
    source [file join $::env(SCRIPT_DIR) build-cmake.inc]
    source [file join $::env(SCRIPT_DIR) run-cmake.inc]
    eval $testscript
    cd ../
}
if {[info exists x86_64_defconfig]} {
    set cmake_props [concat -DPLATFORM=x86_64 -DCAMKES_APP=$appname $extra_cmake_args]
    source [file join $::env(SCRIPT_DIR) build-cmake.inc]
    source [file join $::env(SCRIPT_DIR) run-cmake.inc]
    eval $testscript
    cd ../
}

# Run all the same tests again with MCS configured.
if {[info exists arm_defconfig]} {
    set cmake_props [concat -DARM=TRUE -DPLATFORM=sabre -DCAMKES_APP=$appname -DKernelIsMCS=ON $extra_cmake_args]
    source [file join $::env(SCRIPT_DIR) build-cmake.inc]
    source [file join $::env(SCRIPT_DIR) run-cmake.inc]
    eval $testscript
    cd ../
}
# Also test capDL static allocation for all apps (on ARM)
if {[info exists arm_defconfig]} {
    set cmake_props [concat -DARM=TRUE -DPLATFORM=sabre -DCAMKES_APP=$appname -DKernelIsMCS=ON -DCAmkESCapDLStaticAlloc=TRUE $extra_cmake_args]
    source [file join $::env(SCRIPT_DIR) build-cmake.inc]
    source [file join $::env(SCRIPT_DIR) run-cmake.inc]
    eval $testscript
    cd ../
}
if {[info exists x86_defconfig]} {
    set cmake_props [concat -DPLATFORM=ia32 -DCAMKES_APP=$appname -DKernelIsMCS=ON $extra_cmake_args]
    source [file join $::env(SCRIPT_DIR) build-cmake.inc]
    source [file join $::env(SCRIPT_DIR) run-cmake.inc]
    eval $testscript
    cd ../
}
if {[info exists x86_64_defconfig]} {
    set cmake_props [concat -DPLATFORM=x86_64 -DCAMKES_APP=$appname -DKernelIsMCS=ON $extra_cmake_args]
    source [file join $::env(SCRIPT_DIR) build-cmake.inc]
    source [file join $::env(SCRIPT_DIR) run-cmake.inc]
    eval $testscript
    cd ../
}
if {[info exists riscv]} {
    set cmake_props [concat -DRISCV64=TRUE -DPLATFORM=spike -DCAMKES_APP=$appname $extra_cmake_args]
    source [file join $::env(SCRIPT_DIR) build-cmake.inc]
    source [file join $::env(SCRIPT_DIR) run-cmake.inc]
    eval $testscript
    cd ../
}
