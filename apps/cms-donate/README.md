<!--
     Copyright 2026, Proofcraft Pty Ltd

     SPDX-License-Identifier: CC-BY-SA-4.0
-->

This application tests scheduling context donation for a chain of servers
with a single client.

The client calls the `Intermediate` server component, which forwards each call
to the actual server component. Both servers are passive and the scheduling
context is donated along the chain and returned back to the client.

The passive servers and the scheduling parameters only have an effect on the MCS
kernel. The test will work on the non-MCS kernel.
