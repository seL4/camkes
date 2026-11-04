<!--
     Copyright 2026, Proofcraft Pty Ltd

     SPDX-License-Identifier: CC-BY-SA-4.0
-->

This application tests scheduling context donation with multiple clients and a
single server.

The server prints `All clients done` when it has received a sufficient number of
calls. The clients will finish their own diagnostic printing after that message.
This is expected.

The passive server and the scheduling parameters only have an effect on the MCS
kernel. The test will work on the non-MCS kernel.
