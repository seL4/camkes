<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

# Minimal VGA text example

This application provides a minimal implementation for text mode VGA ternminal. It can be run with:

```
qemu-system-i386 -m 1024 -serial /dev/stdout -vga std -kernel images/kernel-ia32-pc99 -initrd images/capdl-loader-experimental-image-ia32-pc99
```

