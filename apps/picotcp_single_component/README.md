<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

# picotcp\_single\_component

This app contains a single threaded component that echos TCP packets for connections to port 1234
and UDP packets sent to port 1235. It uses picotcp and an ethernet driver in the same address space
to achieve this. Some additional components exist for performing performance measurements.

