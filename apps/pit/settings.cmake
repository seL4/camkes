#
# Copyright 2018, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: BSD-2-Clause
#

# This sample app requires IOAPIC interrupts to be selected
# in order for the correct interrupt handler to be created.
set(KernelIRQController IOAPIC CACHE STRING "" FORCE)
