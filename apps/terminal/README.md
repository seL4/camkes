<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

This is a prototype for a secure terminal system. The system is designed to
provide a GUI where clients can only write to certain parts of the display. It
is setup with two components, one that has the region (0,0) - (15,10) and the
other that has the region (20,20) - (35,30). Each application writes some
sample output (provided as a CAmkES attribute) to its region.

Note that a full secure terminal would use a framebuffer rather than just
console display, but this example is useful for experimentation.
