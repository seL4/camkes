/* Copyright 2015, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <camkes.h>
#include <stdint.h>
#include <stdio.h>
#include "util.h"

int run(void) {
    /* Our IP address, once we're assigned one from the server. */
    uint32_t ip = 0;

    /* Used for debugging later. */
    char pretty_ip[STRLEN_IP];

    /* Synthesise ourselves a unique MAC address. */
    uint64_t hwaddr = make_mac(get_instance_name());
    char pretty_mac[STRLEN_MAC];
    mac_to_string(hwaddr, pretty_mac);
    dprintf("%s: Started with MAC address: %s\n", get_instance_name(), pretty_mac);

    while (ip == 0) {
        dprintf("%s: Sending DHCPDISCOVER\n", get_instance_name());
        uint32_t server_ip;
        uint32_t potential_ip = dhcp_discover(hwaddr, &server_ip);

        ip_to_string(potential_ip, pretty_ip);
        dprintf("%s: Sending DHCPREQ of IP %s\n", get_instance_name(), pretty_ip);
        ip = dhcp_request(potential_ip, server_ip);

        /* If the server rejected this request (DHCPNAK) we'll go round this
         * loop again and retry.
         */
    }

    /* Done. Maybe insert some more interesting stuff here later. */
    ip_to_string(ip, pretty_ip);
    dprintf("%s: Acquired IP %s\n", get_instance_name(), pretty_ip);

    return 0;
}
