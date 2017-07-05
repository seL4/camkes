/* @TAG(NICTA_BSD) */
#include <assert.h>
#include <camkes.h>
#include <stdint.h>
#include <stdio.h>
#include "util.h"

/* Our own IP address */
static uint32_t my_ip = 0xc0a80101; /* 192.168.1.1 */

/* We're going to assign IP addresses from our own subnet (192.168.1.*). The
 * next one we'll assign will be 192.168.1.next_offer_octet, modulo some IP
 * addresses that are off limits. This variable is used to track which IP
 * addresses we've offered previously. Note that it is not a big deal if we
 * offer an IP address that is unavailable/illegal as we can just reject the
 * client's later request for it.
 */
static uint8_t next_offer_octet;

/* Table mapping clients to IP. rounting_table[client_id] = IP address of that
 * client. 0 means unassigned.
 */
static uint32_t routing_table[4] = { 0 };
#define routing_table_sz (sizeof(routing_table) / sizeof(routing_table[0]))

/* Handle a DHCPDISCOVER message. */
static uint32_t discover(uint64_t hwaddr, uint32_t *siaddr) {
    lock_lock();

    /* Figure out a suitable IP address to offer them */
    uint32_t offer;
    do {
        offer = (my_ip & ~0xff) | (uint32_t)next_offer_octet;
        next_offer_octet++;
    } while ((offer & 0xff) == 0 || offer == my_ip || 
             offer == routing_table[0] || offer == routing_table[1] ||
             offer == routing_table[2] || offer == routing_table[3]);

    lock_unlock();

    /* Pass them our IP address so they can pass it back to us when requested
     * IP assignment. This thing is in the DHCP spec to allow for multiple DHCP
     * servers on the same network.
     */
    *siaddr = my_ip;
    
    char pretty_ip[STRLEN_IP];
    ip_to_string(offer, pretty_ip);
    dprintf("%s: Sending DHCPOFFER of IP %s\n", get_instance_name(), pretty_ip);

    return offer;
}

/* Handle a DHCPREQ message */
static uint32_t request(unsigned int client, uint32_t ip, uint32_t siaddr) {

    if (siaddr != my_ip) {
        /* This message was intended for a different DHCP server. In a real
         * system we wouldn't send a DHCPNAK here, but would just ignore this
         * message. In this simulated setup we are the only server and we
         * *must* send a reply, so we just NAK it.
         */
        dprintf("%s: Sending DHCPNAK due to server IP mismatch\n",
            get_instance_name());
        return 0;
    }

    assert(client < routing_table_sz && "DHCPREQ from non-existent client");

    lock_lock();

    /* IP address the client gets. This will remain 0 after the logic below if
     * we're denying the client's request.
     */
    uint32_t assigned = 0;

    if (routing_table[client] == ip) {
        /* They requested their existing IP. OK, whatever. */
        dprintf("%s: Sending DHCPACK to client %u for its existing IP\n",
            get_instance_name(), client);
        assigned = ip;

    } else if (ip != my_ip && ip != 0 && ip != routing_table[0] &&
            ip != routing_table[1] && ip != routing_table[2] &&
            ip != routing_table[3]) {
        /* They requested an IP that was not ours, 0 or in the routing table
         * already. XXX: we should probably block the broadcast IP here too.
         */
        char pretty_ip[STRLEN_IP];
        ip_to_string(ip, pretty_ip);
        dprintf("%s: Sending DHCPACK to client %u of IP %s\n",
            get_instance_name(), client, pretty_ip);
        routing_table[client] = ip;
        assigned = ip;
    }

    lock_unlock();
    return assigned;
}

uint32_t client1_discover(uint64_t hwaddr, uint32_t *siaddr) {
    return discover(hwaddr, siaddr);
}

uint32_t client2_discover(uint64_t hwaddr, uint32_t *siaddr) {
    return discover(hwaddr, siaddr);
}

uint32_t client3_discover(uint64_t hwaddr, uint32_t *siaddr) {
    return discover(hwaddr, siaddr);
}

uint32_t client4_discover(uint64_t hwaddr, uint32_t *siaddr) {
    return discover(hwaddr, siaddr);
}

uint32_t client1_request(uint32_t ip, uint32_t siaddr) {
    return request(0, ip, siaddr);
}

uint32_t client2_request(uint32_t ip, uint32_t siaddr) {
    return request(1, ip, siaddr);
}

uint32_t client3_request(uint32_t ip, uint32_t siaddr) {
    return request(2, ip, siaddr);
}

uint32_t client4_request(uint32_t ip, uint32_t siaddr) {
    return request(3, ip, siaddr);
}
