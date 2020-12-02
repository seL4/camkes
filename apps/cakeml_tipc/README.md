<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

# CAmkES + CakeML + TIPC example application

This example application demonstrates the use of a CakeML component acting as a filter between C components. All components
in the system communicate using the Transparent IPC protocol (TIPC). The TIPC protocol is facilitated by the implementation
of VirtQueues. This example system contains 4 client components passing around a message in a round robin configuration,
collectively incrementing a counter. There exists a CakeML filter between 2 of the 4 clients. The filter simply passes the
data onto the next destination component.

## Setting up HOL and CakeML

### Install polyml

Both polyml and and libpolyml.a are required for HOL and CakeML. On debian these can be found by installing the following packages

 * polyml
 * libpolyml-dev

### Checkout sources

Assuming no existing HOL and CakeML then first cakeML must be checked out from

 * https://github.com/HOL-Theorem-Prover/HOL
 * https://github.com/CakeML/cakeml

Different versions of CakeML and HOL may or may not be compatiable, determing this
is beyond the scope of this README

A copy of the prebuilt CakeML compiler (`cake`) is also required and can be downloaded from https://cakeml.org/cake-x64-64.tar.gz

For now we will assume these are checked out in HOL_PATH and CAKEML_PATH

### Build HOL

```sh
$ cd HOL_PATH
$ poly < tools/smart-configure.sml
$ bin/build
```

On Debian based distros and some others you may also need to

```sh
$ cd HOL_PATH
$ echo 'val polymllibdir = "/usr/lib/x86_64-linux-gnu";' > tools-poly/poly-includes.ML
```

## Required paths

The CakeML integration in this build system requires the following things

 * HOL_PATH/bin be in the system PATH (this is so that the Holmake executable can be found)
 * the `cake` executable (i.e. the prebuilt CakeML compiler) be on the system PATH
 * either the environment variable CAKEMLDIR=CAKEML_PATH be set or -DCAKEMLDIR=CAKEML_PATH be passed when initializing cmake

## Building + running

In the root camkes directory initialize with

```sh
$ mkdir name_of_build_dir
$ cd name_of_build_dir
$ ../init-build.sh -DPLATFORM=[x86_64|exynos5410|exynos5422] -DCAMKES_APP=cakeml_tipc -DCAKEMLDIR=CAKEML_PATH
$ ninja
$ ./simulate
```

Although -DCAKEMLDIR=CAKEML_PATH can be left out if the CAKEMLDIR environment variable has already been set

Running the application should produce the following output:

```
...
Booting all finished, dropped to user space
Client 0 sending first message
CakeMLFilter forwarding message
Client 1 recieved payload value: 1
Client 2 recieved payload value: 2
Client 3 recieved payload value: 3
Client 0 recieved payload value: 4
CakeMLFilter forwarding message
Client 1 recieved payload value: 5
Client 2 recieved payload value: 6
Client 3 recieved payload value: 7
Client 0 recieved payload value: 8
CakeMLFilter forwarding message
Client 1 recieved payload value: 9
Client 2 recieved payload value: 10
Client 3 recieved payload value: 11
Client 0 recieved payload value: 12
CakeMLFilter forwarding message
Client 1 recieved payload value: 13
Client 2 recieved payload value: 14
Client 3 recieved payload value: 15
Client 0 recieved payload value: 16
CakeMLFilter forwarding message
Client 1 recieved payload value: 17
Client 2 recieved payload value: 18
Client 3 recieved payload value: 19
Client 0 recieved payload value: 20
```
