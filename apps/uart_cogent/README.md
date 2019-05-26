<!--
     Copyright 2019, Data61
     Commonwealth Scientific and Industrial Research Organisation (CSIRO)
     ABN 41 687 119 230.

     This software may be distributed and modified according to the terms of
     the BSD 2-Clause license. Note that NO WARRANTY is provided.
     See "LICENSE_BSD2.txt" for details.

     @TAG(DATA61_BSD)
-->
# uart_cogent

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
