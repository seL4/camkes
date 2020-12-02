#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(dhcp C)

set(configure_string "")

config_option(DHCPDebug APP_DHCP_DEBUG "Enable debug print outs for this application." DEFAULT ON)

add_config_library(app_dhcp "${configure_string}")

DeclareCAmkESComponent(Client SOURCES src/client.c src/util.c INCLUDES src LIBS app_dhcp_Config)
DeclareCAmkESComponent(Server SOURCES src/server.c src/util.c INCLUDES src LIBS app_dhcp_Config)

DeclareCAmkESRootserver(dhcp.camkes)
add_simulate_test([=[wait_for "a: Acquired IP 192.168.1.5"]=])
