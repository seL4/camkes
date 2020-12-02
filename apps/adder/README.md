<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

This application demonstrates the use of dataport wrapper to pass pointers via CAmkES RPC
across different components. Although users still need to declare a dataport and cannot
have pointers in the user-defined structure, users do not need to worried about how
arguments are encapsulated and can have a cleaner interface at least.
