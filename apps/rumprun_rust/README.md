<!--
     Copyright 2017, Data61
     Commonwealth Scientific and Industrial Research Organisation (CSIRO)
     ABN 41 687 119 230.

     This software may be distributed and modified according to the terms of
     the BSD 2-Clause license. Note that NO WARRANTY is provided.
     See "LICENSE_BSD2.txt" for details.

     @TAG(DATA61_BSD)
-->

# Rumpkernel running a simple rust application

This application demonstrates a simple rust hello world program that runs in a 
rumprun unikernel instance on CAmkES on seL4. Second rumpkernel runs a simpe hello app.

## Prerequisities
* Install Rust using Rustup: `curl https://sh.rustup.rs -sSf | sh`
* Setup rust:
```
rustup update nightly
rustup target add x86_64-rumprun-netbsd
rustup override set nightly
```
