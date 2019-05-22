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

project(dhcp C)

set(configure_string "")

config_option(DHCPDebug APP_DHCP_DEBUG
    "Enable debug print outs for this application."
    DEFAULT ON
)

add_config_library(app_dhcp "${configure_string}")

DeclareCAmkESComponent(Client SOURCES src/client.c src/util.c INCLUDES src LIBS app_dhcp_Config)
DeclareCAmkESComponent(Server SOURCES src/server.c src/util.c INCLUDES src LIBS app_dhcp_Config)

DeclareCAmkESRootserver(dhcp.camkes)
