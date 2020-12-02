<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: GPL-2.0-only
-->

This application demonstrates how to use a binary semaphore to turn an
asynchronous interface (ie. where a callback is invoked by an interrupt handler)
into a synchronous camkes interface. A periodic event is used to simulate an
interrupt.
