/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#include <autoconf.h>
#include <app_dhcp/gen_config.h>
#include <stdint.h>
#include <stdio.h>

/* Generate a MAC-like address from some arbitrary string data. */
uint64_t make_mac(const char *data);

/* The number of bytes required for the 'output' argument in mac_to_string. */
#define STRLEN_MAC 18

/* Convert a 48-bit MAC address stored in the 'input' into a pretty-printed
 * form in the output.
 */
void mac_to_string(uint64_t input, char *output);

/* The number of bytes required for the 'output' argument in ip_to_string. */
#define STRLEN_IP 16

/* Convert a 32-bit IP address stored in the 'input' into a pretty-printed
 * form in the output.
 */
void ip_to_string(uint32_t input, char *output);

#ifdef CONFIG_APP_DHCP_DEBUG
#define dprintf(args...) printf(args)
#else
#define dprintf(args...) do { } while (0)
#endif
