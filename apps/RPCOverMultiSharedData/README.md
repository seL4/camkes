<!--
     Copyright 2020, Data61
     Commonwealth Scientific and Industrial Research Organisation (CSIRO)
     ABN 41 687 119 230.

     This software may be distributed and modified according to the terms of
     the BSD 2-Clause license. Note that NO WARRANTY is provided.
     See "LICENSE_BSD2.txt" for details.

     @TAG(DATA61_BSD)
-->

This application demonstrates the use of the seL4RPCOverMultiSharedData to perform
RPC using shared memory buffers between the client and server. This allows for transferring
data larger than what can fit in an seL4 IPC buffer. The generated stubs will copy the
arguments into the shared buffer and then copy them out again on each side.
