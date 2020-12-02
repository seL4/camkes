<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

This application demonstrates the use of the seL4RPCOverMultiSharedData to perform
RPC using shared memory buffers between the client and server. This allows for transferring
data larger than what can fit in an seL4 IPC buffer. The generated stubs will copy the
arguments into the shared buffer and then copy them out again on each side.
