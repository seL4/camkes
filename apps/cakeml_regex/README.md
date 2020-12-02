<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

# CAmkES CakeML Filter

This app is a CAmkES filter component written in CakeML, for running atop seL4.

## System Overview

The CAmkES system defined here consists of three components: Producer, Consumer and CakeMLFilter. The Producer emits strings over IPC to the CakeMLFilter, which matches them against a regular expression and either forwards them via IPC to the Consumer (if they match), or drops them (if they do not). The CakeMLFilter is accompanied by proofs within the HOL4 proof assistant which guarantee that the implementation of regular expression matching is correct.

## Getting Started

Create a new project directory and use Google's `repo` tool to check out this
repository and supporting code:

```
mkdir cakeml-regex-filter
cd cakeml-regex-filter
repo init -u https://github.com/seL4/camkes-manifest.git
repo sync
```

With CakeML checked out to `/path/to/cakeml` (see the [Dependencies](#Dependencies) section below), create a build directory and build the project:

```
mkdir build
cd build
../init-build.sh -DCAKEMLDIR=/path/to/cakeml -DCAMKES_APP=cakeml_regex
ninja
```

Run the compiled project on QEMU using the provided simulate script:

```
./simulate
```

You should see some kernel start-up messages followed by the output:

```
This will get through 1
This will get through 2
This will get through 3
...
```

(press `Ctrl-A X` to exit QEMU)

These strings were sent by the Producer component, accepted by the filter, and printed out by the Consumer. If you look at the source for the Producer, you will see that it also sends other strings that do not match the default regular expression, and are therefore dropped.

All the project-specific source code lives in `projects/cakeml`, and within that directory, the most relevant source files are:

* `components/Producer/producer.c`: sends strings over IPC to the filter
* `components/CakeMLFilter/filterProgScript.sml`: definition of the regex matching machinery
* `components/CakeMLFilter/componentProgScript.sml`: filters the strings it receives, and outputs them using the `#(emit_string)` FFI call
* `components/Consumer/consumer.c`: prints all of the strings it receives via IPC to stdout

Throughout the rest of this document, we will often use paths to refer to files relative to `projects/cakeml`.

## Implementation Details

### Dependencies

* Google's repo tool
* seL4 and CAmkES dependencies: https://docs.sel4.systems/HostDependencies
* A checkout of the CakeML repository: https://github.com/CakeML/cakeml
    + This commit from Nov 26 2018 is known to work: `59886cd0205c1d5d943ef10a26890f79b515b68f`
* A built checkout of HOL4 with the `bin` directory on your `$PATH`: https://github.com/HOL-Theorem-Prover/HOL
    + This commit from Nov 26 2018 is known to work: `7f7650b1f7d9fbc79f55646dabcf225b5cf0fff4`
* A copy of the CakeML binary compiler: https://cakeml.org/regression.cgi/job/587

### How CAmkES works

A CAmkES system consists of several _components_, communicating via
_connections_. In our example system, we have three components called Producer, Consumer and CakeMLFilter, which communicate via two RPC connections, configured in `apps/cakeml-filter/cakeml-filter.camkes`. This `.camkes` file describes the structure of the system in a way that allows the CAmkES tool to generate C "glue code" to join the components together into a running system. Each component is also specified in its own `.camkes` file, which describes the properties of the component (like whether it has a control thread) and any interfaces it provides or uses.

For general information on CAmkES, please see the documentation:

* https://sel4.systems/Info/CAmkES/About.pml
* https://github.com/seL4/camkes-tool/blob/master/docs/index.md

### Filter Implementation

The filter is an I/O wrapper around the code that the HOL4-to-CakeML translator ([Myreen & Owens 2012][myreen-owens-2012]) generates when fed Konrad Slind's regular expression matcher and Michael Norrish's regular expression parser. The resulting deeply embedded CakeML program is pretty-printed as an S-expression (using infrastructure by Nicholas Coughlin), and compiled to binary using the bootstrapped CakeML compiler.

The filter is adapted from the CakeML `grep` implementation, available here:

* https://github.com/CakeML/cakeml/blob/master/examples/grepProgScript.sml

We make use of the CakeML support in CAmkES to define the filter component with a minimum of boilerplate. CAmkES generates a CakeML event loop that waits on the appropriate endpoint, deserialise the arguments, and passes them to the appropriate CakeML handler function. Our handler function, `client_transfer_string` checks the input with the verified regular expression matcher. If the input matches the regular expression, the CakeML program calls `ffiemit_string` (using the syntax `#(emit_string)`), which calls the CAmkES generated C function `server_transfer_string` to send the string to the Consumer.

Both the producer and the consumer are implemented in C.

### Customising the Filter Regex

The regular expression (regex) that is used for filtering is configured through the cakeml_regex.camkes `configuration` section.

```
    configuration {
        cakemlfilter.filter_regex = "This.*";
    }
```

The regular expression should be provided as a Standard ML string, using the operators and syntax defined here:

* https://github.com/HOL-Theorem-Prover/HOL/tree/master/examples/formal-languages/regular

## Checking the Proofs

The proofs are contained in the `filterProgScript.sml` file, alongside the definitions for the CakeML filter. The build system automatically checks the proofs when building the system image. To step through them manually, it's easiest to run a build, and then run `hol` and the editor of your choice in the `build/projects/cakeml/apps/cakeml-filter` directory. For Emacs and Vim support, see the HOL4 repo:

https://github.com/HOL-Theorem-Prover/HOL/tree/master/tools

## What the Proofs Say

* Under the assumption that FFI calls behave as expected, and that the program doesn't run out of memory, the compiled CakeML program will not crash, and will execute in a manner compatible with its semantics. This property is true of all programs compiled by the CakeML compiler, although because we are using the compiler binary directly, we do not actually construct this theorem specialised to our program within HOL4.
* The regular expression matching function returns true if and only if the string being matched is in the regular language induced by the regular expression.

## Known Limitations

* Unverified CAmkES glue code: the interaction between the CAmkES event loop, the (un)marshalling code and the component implementation is currently unverified.
* The extraction from HOL4 to S-expressions is trusted. For a nicer trust story, we could: (a) compile in-logic to get a theorem about the binary, though it takes a long time; or (b) use a verified printer to S-expressions or concrete syntax.

[myreen-owens-2012]: http://www.cl.cam.ac.uk/~mom22/miniml/hol2miniml.pdf
