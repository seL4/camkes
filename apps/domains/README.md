<!--
     Copyright 2026, Proofcraft Pty Ltd

     SPDX-License-Identifier: CC-BY-SA-4.0
-->

# Domains

This application demonstrates the use of the seL4 domain scheduler with CAmkES.

It is based on the [event](../event/) app as a minimal example and does not
do anything particularly useful. It just shows which attributes to set and how
to use the domain schedule.

The example uses 3 domains: 0, 1, and 2. Domain 0 runs the intialiser and
debugging code (fault handlers). Domain 1 runs the event source component, and
domain 2 runs the event sink component and waiting thread.

The schedule is set up such that domain 1 will generate a lot of events before
the sink in domain 2 can pick up the first one. That is, the output log should
show only a few received events, not many as in the original `event` app. This
is not a particularly useful setup, but it shows that the schedule is in effect.
If you change the schedule to make domain 1 run for a shorter amount of time,
domains 2 will see more events, because it gets to run more often.
