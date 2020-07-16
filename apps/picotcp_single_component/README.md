<!--
     Copyright 2020, Data61
     Commonwealth Scientific and Industrial Research Organisation (CSIRO)
     ABN 41 687 119 230.

     This software may be distributed and modified according to the terms of
     the BSD 2-Clause license. Note that NO WARRANTY is provided.
     See "LICENSE_BSD2.txt" for details.

     @TAG(DATA61_BSD)
-->

# picotcp_single_component

This app contains a single threaded component that echos TCP packets for connections to port 1234
and UDP packets sent to port 1235. It uses picotcp and an ethernet driver in the same address space
to achieve this. Some additional components exist for performing performance measurements.

