<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
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
