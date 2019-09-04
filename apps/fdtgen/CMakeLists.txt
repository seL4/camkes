# @TAG(DATA61_BSD)
cmake_minimum_required(VERSION 3.7.2)

project(fdtgen C)

# This only works on sabre
if(
    NOT
    "${KernelArch}"
    STREQUAL
    "arm"
    OR
        NOT
        "${KernelARMPlatform}"
        STREQUAL
        "sabre"
)
    message(FATAL_ERROR "fdtgen application is only supported on Arm sabre")
endif()

set(CAmkESDTS ON CACHE BOOL "" FORCE)

DeclareCAmkESComponent(Client SOURCES main.c fdt_utils.c LIBS fdtgen)

DeclareCAmkESRootserver(main.camkes)
