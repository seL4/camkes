<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

# PicoServer

This is a sample application which uses the PicoServer component as well as the
Ethdriver component to demonstrate networking on CAmkES. There are two
components, Echo and Listener. Echo will listen on a particular port (in this
case, 1234) and forward any messages to Listener. Listener will then print the
message out via the serial port.

Usage:
    netcat <IP address> 1234

Config
------

There are some configuration options that may need to be changed. The
configuration options lie inside the picoserver.camkes file.

These include:
    - IP address to assign to the PicoServer component, see picoserver.ip_addr,
      and the CMake variable PICOSERVER_IP_ADDR
    - MAC address of the device, see picoserver.ethdriver_mac
    - If on x86, the hardware details of Ethernet device, which includes:
        * Physical address of the base of the memory-mapped device
        * Size of the memory region
        * IRQ-related information (PCI, MSI, etc)
        * IO spaces and ID of the device
        * PCI bus/dev/function information of the device
    - If on ARM, the Ethdriver component supports two boards at this time of
      writing (24/04/19), the IMX6 and the ZYNQ7000. Promiscuous mode can be
      turned on by setting ethdriver.promiscuous_mode to 1, otherwise off if
      set to 0. Look at the Ethdriver component inside the global-components
      repository, and libethdrivers inside the util_libs repository for adding
      support to another board.
