<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

# UART driver in Cogent

Prototype cogent UART driver for sabre.  Need to have cogent installed and repository
checked out in `./tools/cogent`.

## To build

```sh
mkdir build
cd build
../init-build.sh -DCAMKES_APP=uart_cogent -DPLATFORM=sabre
ninja

```

## To run

```
$ ./simulate
qemu-system-arm -machine sabrelite  -nographic -s -serial null -serial mon:stdio -m size=1024M  -kernel images/capdl-loader-image-arm-imx6

ELF-loader started on CPU: ARM Ltd. Cortex-A9 r0p0
  paddr=[20000000..2025bfff]
ELF-loading image 'kernel'
  paddr=[10000000..10036fff]
  vaddr=[e0000000..e0036fff]
  virt_entry=e0000000
ELF-loading image 'capdl-loader'
  paddr=[10037000..10181fff]
  vaddr=[10000..15afff]
  virt_entry=1e518
Enabling MMU and paging
Jumping to kernel-image entry point...

Bootstrapping kernel
Warning: Could not infer GIC interrupt target ID, assuming 0.
Booting all finished, dropped to user space
This message is sent via UART.
Input from UART: f
Input from UART: g
Input from UART: d
Input from UART: g
Input from UART: q
UART client exit...
```
