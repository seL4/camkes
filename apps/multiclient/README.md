<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

This is a example of showing multiple clients share one connection.

There are one server(Echo) and three clients(Client and Sender, Client has two instances).
1. All of the three clients connect to the same RPC interface that the server provides.
2. When the server emits a event, all of the clients will receive it.
3. The dataport is shared among the server and the clients. Note that, the clients can see
   each other's data in the dataport.

Those connections run in separate threads which could cause race conditions potentially.
It is the user's responsibility to apply proper locking mechanism if the underlying
functions are not reentrant.
