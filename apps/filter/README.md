<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

This application demonstrates the use of a component to filter communication
from another. In this setup, 'filter' is placed in-between 'client' and 'store'
and prevents 'client' reading the value of a secret via its interface. In a
sense, 'client' can be fooled into thinking it is talking directly to 'store'.
