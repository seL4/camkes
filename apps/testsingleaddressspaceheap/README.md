<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

This application tests that the heaps of colocated component instances do not
overlap. Previously, the semantics of single address space components was that
component instances would end up sharing an enlarged heap. This has some subtle
issue and we now separate the component instances' heaps. This application
tests that these semantics are currently used.
