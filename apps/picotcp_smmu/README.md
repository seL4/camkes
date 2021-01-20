<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: CC-BY-SA-4.0
-->

# picotcp_smmu

This app contains a single threaded component that echoes UDP packets for
connections to port 1235. It uses picoTCP and an ethernet driver in the same
address space to achieve this. Additionally, this application is intended to be
used with an SMMU to demonstrate the capabilities of a SMMU.
