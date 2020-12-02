<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

This application demonstrates the use of a dataport and global async connectors to
communicate across different components. The sender component sends a random string
value onto the client, who in turn processes the string and replies to confirm it
recieved the event. This example was done using global async connectors such that
each component is single threaded.
