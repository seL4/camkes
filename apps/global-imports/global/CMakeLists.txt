#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

add_subdirectory(components/Printer)
add_subdirectory(components/Server)

add_subdirectory(interfaces/GetterIface)
add_subdirectory(interfaces/PrinterIface)

# Now add our search directories so that the the components and interfaces are
# actually found by camkes
CAmkESAddImportPath(components interfaces)
