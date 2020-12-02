<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

# CAmkES + CakeML example application

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
$ ../init-build.sh -DPLATFORM=x86_64 -DCAMKES_APP=cakeml_hello -DCAKEMLDIR=CAKEML_PATH
$ ninja
$ ./simulate
```

Although -DCAMKELDIR=CAKEML_PATH can be left out if the CAKEMLDIR environment variable has already been set
