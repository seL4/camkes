# Swap Counter Example

This directory contains a simple CAmkES example the was used for demonstration
purposes in a submission to [Formal Methods 2015](http://fm2015.ifi.uio.no/).
The following instructions describe how to obtain and build the code and
theories discussed in the paper, Fernandez et al,
_Automated Verification of RPC Stub Code_.

Some of these instructions duplicate steps from other seL4-related repositories
and infrastructure. These instances are noted and, where you have already
performed the associated steps, you can safely skip the section.

## Prerequisites

The instructions that follow assume the following environment:

* 4GB RAM
  * Building the AutoCorres heap image will likely require at least 4GB of
    available memory.
* 64-bit environment
  * While none of the tools or installation steps are known to be incompatible
    with a 32-bit environment, the requirement for at least 4GB RAM may
    necessitate this.
* Ubuntu Linux 14.04
  * None of the steps are known to depend on the Ubuntu distribution, but this
    is the environment we have tested in. The process for generating code and
    theories requires a Linux environment and will not work on Mac OS or
    Windows.
* 20GB free disk space
  * Proof images, associated dependencies and generated files will likely
    occupy at least this much space.
* Internet connection
  * Some of the package installation steps and Isabelle setup require various
    dependencies that are hosted online and fetched on-demand.

## Pre-install Steps

First, update your package manager's cache. This ensures you will be able to
fetch all the dependencies described below.

```bash
sudo apt-get update
```

## Dependencies

### Version Control Tools

If you are reading this file on your local computer, you have likely already
successfully installed the necessary version control tools and cloned the
manifest for this project. If not, you will need the Git and Subversion version
control systems and Google Repo.

```bash
sudo apt-get install git subversion

# Configure git
git config --global user.email '<you@example.com>'
git config --global user.name 'CAmkES User'

wget https://storage.googleapis.com/git-repo-downloads/repo -O ~/repo
chmod +x ~/repo
export PATH=${PATH}:${HOME}
```

### C Compiler

This section duplicates generic steps from
[setting up CAmkES](http://sel4.systems/CAmkES/GettingStarted.pml) and can be
safely skipped if you have already followed these.

The example and the associated proofs are intended to apply to code compiled
for an ARM processor. For this, you need an ARM cross compiler. Install this
with the following commands.

```bash
sudo apt-get install build-essential gcc-arm-none-eabi
```

### Emulator

This section duplicates generic steps from
[setting up CAmkES](http://sel4.systems/CAmkES/GettingStarted.pml) and can be
safely skipped if you have already followed these.

If you want to run the compiled component system, you will need either
available hardware or a software emulator. To install a software emulator, run
the following commands. If you are only intending to run the proofs, you do not
need this.

```bash
sudo apt-get install qemu
```

### Libraries

This section duplicates generic steps from
[setting up CAmkES](http://sel4.systems/CAmkES/GettingStarted.pml) and
[C pruner setup](https://github.com/seL4/pruner) and can be safely skipped if
you have already followed these.

The CAmkES and seL4 build systems rely on several libraries that are not
installed by default. To install them, run the following commands.

```bash
sudo apt-get install lib32z1 lib32ncurses5 lib32bz2-1.0 libxml2-utils \
  realpath libglib2.0-dev libglib2.0-0
```

### Python Modules

This section duplicates generic steps from
[setting up CAmkES](http://sel4.systems/CAmkES/GettingStarted.pml) and can be
safely skipped if you have already followed these.

The CAmkES component platform depends on several Python modules. Some of these
are not available through the standard Ubuntu repositories and need to be
retrieved from the Python package manager, `pip`.

```bash
sudo apt-get install python-jinja2 python-ply python-tempita

# Pyelftools is not available in the standard Ubuntu repositories.
sudo apt-get install python-pip
pip install --user pyelftools
```

### Haskell Modules

This section duplicates generic steps from
[setting up CAmkES](http://sel4.systems/CAmkES/GettingStarted.pml) and can be
safely skipped if you have already followed these.

The code and theory generation process relies on an intermediate tool written
in Haskell. To build this, you will need a Haskell compiler and several Haskell
modules. Install these with the following commands.

```bash
# Install Haskell compiler
sudo apt-get install ghc

# Install Haskell package manager
sudo apt-get install cabal-install

# Update Haskell package manager cache
cabal update

# Install necessary modules.
cabal install --user MissingH data-ordlist split
```

### Perl Modules

This section duplicates generic steps from
[setting up l4.verified](https://github.com/seL4/l4v) and can be safely skipped
if you have already followed these.

Isabelle requires a Perl module to retrieve its further dependencies. Install
this with the following command.

```bash
sudo apt-get install libwww-perl
```

### Clang/LLVM

This section duplicates steps from
[getting started with Clang](http://clang.llvm.org/get_started.html).

For performing intermediate code transformations, CAmkES relies on Clang/LLVM.
You will need to build the Clang/LLVM ecosystem from source. To do this, run
the following commands.

```bash
svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm

cd llvm/tools
svn co http://llvm.org/svn/llvm-project/cfe/trunk clang
cd ../..

cd llvm/tools/clang/tools
svn co http://llvm.org/svn/llvm-project/clang-tools-extra/trunk extra
cd ../../../..

cd llvm/projects
svn co http://llvm.org/svn/llvm-project/compiler-rt/trunk compiler-rt
cd ../..

mkdir llvm-build
cd llvm-build
../llvm/configure --prefix=${HOME}/llvm-install
make
make install
cd ..
```

## Installation

### Clone Repository manifest

If you are reading this file locally, you have likely already cloned the
project manifest and can safely skip this section. If not, if you have correctly
installed the [version control tools](#versioncontroltools) from above, you
should be able to clone the project manifest with the following commands.

```bash
mkdir camkes
cd camkes
repo init -u https://github.com/seL4/camkes-manifest -b FM2015
repo sync
```

### Install Isabelle

The Isabelle theorem prover requires some installation steps itself. This
section duplicates setup steps from the
[l4.verified setup](https://github.com/seL4/l4v/) and can safely be skipped if
you understand and have followed these steps.

```bash
mkdir -p ~/.isabelle/etc
cp -i l4v/misc/etc/settings ~/.isabelle/etc/settings
./isabelle/bin/isabelle components -a
./isabelle/bin/isabelle jedit -bf
./isabelle/bin/isabelle build -bv HOL-Word
```

## Code and Proof Generation

Having successfully followed the previous steps, you should now be ready to run
this example. Run the following commands to generate code, proofs and an
executable binary.

```bash
# Setup example configuration
make arm_swapcounter_defconfig
make silentoldconfig

# Configure path to LLVM
sed -i \
  's/^CONFIG_CAMKES_LLVM_PATH.*$/CONFIG_CAMKES_LLVM_PATH="~\/llvm-install"/g' \
  .config

# Build example
make
```

This process produces three artefacts of note:

* images/capdl-loader-experimental-image-arm-imx31 -- This is an image
    containing the compiled seL4 kernel, a userspace loader and the component
    system described in this directory.
* build/arm/imx31/swapcounter/thy/conn/generated/conn_pruned.c_pp -- This is a
    minimised, consolidated version of the generated glue code relevant to this
    system.
* build/arm/imx31/swapcounter/thy/conn/generated/conn.thy -- This is an
    Isabelle theory containing generated lemmas and associated proofs of the
    correctness of the previously mentioned glue code.

### Running the System

To execute the system, you will need either available hardware or the Qemu
emulator, described [above](#emulator). The process for running the image on
hardware will depend on your bootloader and method of access, for which
instructions are not provided here. To run the image in the Qemu emulator, run
the following commands.

```bash
qemu-system-arm -M kzm -nographic -kernel \
  images/capdl-loader-experimental-image-arm-imx31
# Press Ctrl+A to exit the emulator
```

You will only see output related to the kernel and userspace loader, as the
component system itself does not print anything.

### Running the Proofs

The generated theory of correctness and the generated code itself need to be
hosted within l4.verified. To do this, copy them into l4v:

```bash
cp build/arm/imx31/swapcounter/thy/conn/generated/conn_pruned.c_pp \
  l4v/camkes/glue-proofs/
cp build/arm/imx31/swapcounter/thy/conn/generated/conn.thy \
  l4v/camkes/glue-proofs/
```

Now, you can open Isabelle's jEdit interface to run and explore the generated
theory:

```bash
cd l4v/camkes/glue-proofs
../../../isabelle/bin/isabelle jedit -d ../.. -l AutoCorres conn.thy
```

For detailed descriptions of what the lemma statements are expressing and how
the generated proofs are put together, please refer to our paper in Formal
Methods 2015.

## Questions and Troubleshooting

Any issues with using this example or repository can be addressed to Matthew
Fernandez
&lt;[matthew.fernandez@nicta.com.au](mailto:matthew.fernandez@nicta.com.au)&gt;.
