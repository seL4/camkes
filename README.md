<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: CC-BY-SA-4.0
-->

# CAmkES

This repository contains various CAmkES applications, default configurations
and testing scripts.

```
  apps/       Example applications
  configs/    Default configurations
  test/       Testing scripts
```

This is not a standalone repository. Checkout the `camkes-manifest` repository or
go to our website for details.

The applications in this repository are:

`adder`: demonstrates the use of dataport wrapper to pass pointers via CAmkES RPC

`epit`: demonstrates the use of CAmkES interrupt connector to receive hardware interrupts

`exchangestring`: demonstrates how to pass string arguments between components

`filter`: demonstrates the use of a component to filter communication

`global-imports`:

`hierarchical-attributes`:

`hierarchical-components`:

`keyboard`: demonstrates the use of IO ports and interrupts in a CAmkES component

`lockserver`: demonstrates how to use built-in mutex

`multiassembly`:

`multiclient`: domonstrates multiple clients sharing one connection

`multiplier`: demonstrates the use of arrays as arguments

`mutex`: demonstrates the use of user-defined connectors in CAmkES

`rotate`: demonstrates the use of user-defined types as the arguments of an interface

`swapcounter`:

`socket`: demonstrates the use of user-defined dataports

`structs`: demonstrates the use of struct and array attributes

`terminal`: a prototype for a secure terminal system

`uart`: demonstrates how to access hardware device memory
