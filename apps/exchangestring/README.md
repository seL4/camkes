<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

This application demonstrates how to pass string arguments between components. All strings
must be '\0' terminated. Note that the client(caller) is responsible for freeing the
memory of "out/inout" typed arguments.
