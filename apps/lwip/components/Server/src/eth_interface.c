/*
 * Copyright 2019, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <autoconf.h>

#include <string.h>
#include <camkes.h>

/* remove the camkes ERR_IF definition to not overlap with lwip */
#undef ERR_IF

#include <ethdrivers/raw.h>
#include <ethdrivers/lwip.h>

#include <sel4/sel4.h>
#include <sel4utils/sel4_zf_logif.h>

#include <lwip/lwipopts.h>

#include <lwip/init.h>
#include <lwip/netif.h>
#include <lwip/timeouts.h>
#include <lwip/udp.h>

#include <netif/etharp.h>

static lwip_iface_t lwip_driver = {0};

static void low_level_init(struct eth_driver *driver, uint8_t *mac, int *mtu)
{
    // 1500 is the standard ethernet MTU at the network layer.
    *mtu = 1500;
    ethdriver_mac(&mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
}

extern void *ethdriver_buf;

static void raw_poll(struct eth_driver *driver)
{
    int len;
    int status;
    status = ethdriver_rx(&len);
    while (status != -1) {
        void *buf;
        void *cookie;
        buf = (void *)driver->i_cb.allocate_rx_buf(driver->cb_cookie, len, &cookie);
        if (buf) {
            // Only proceed if we successfully got a buffer. If not, the packet will simply be dropped.
            // UDP doesn't mind, and the packet will be resent for TCP due to us not sending an ACK.
            // This prevents crashing in a DDOS attack or malicious packet that is too large.
            memcpy(buf, (void *)ethdriver_buf, len);
            driver->i_cb.rx_complete(driver->cb_cookie, 1, &cookie, (unsigned int *)&len);
        }

        if (status == 1) {
            status = ethdriver_rx(&len);
        } else {
            /* if status is 0 we already saw the last packet */
            assert(status == 0);
            status = -1;
        }
    }
}

static int raw_tx(struct eth_driver *driver, unsigned int num, uintptr_t *phys, unsigned int *len, void *cookie)
{
    unsigned int total_len = 0;
    int i;
    void *p = (void *)ethdriver_buf;
    for (i = 0; i < num; i++) {
        memcpy(p + total_len, (void *)phys[i], len[i]);
        total_len += len[i];
    }
    ethdriver_tx(total_len);
    return ETHIF_TX_COMPLETE;
}

static void handle_irq(struct eth_driver *driver, int irq)
{
    raw_poll(driver);
}

void interface_tick() {
    handle_irq(&lwip_driver.driver, 0);
}

static struct raw_iface_funcs iface_fns = {
    .raw_handleIRQ = handle_irq,
    .print_state = NULL,
    .low_level_init = low_level_init,
    .raw_tx = raw_tx,
    .raw_poll = raw_poll
};

static int ethdriver_init(struct eth_driver *eth_driver, ps_io_ops_t io_ops, void *config)
{
    eth_driver->eth_data = NULL;
    eth_driver->dma_alignment = 1;
    eth_driver->i_fn = iface_fns;
    return 0;
}

static void *malloc_dma_alloc(void *cookie, size_t size, int align, int cached, ps_mem_flags_t flags)
{
    assert(cached);
    int error;
    void *ret = malloc(size);
    if (ret == NULL) {
        ZF_LOGE("ERR: Failed to allocate %d\n", size);
        return NULL;
    }
    return ret;
}

static void malloc_dma_free(void *cookie, void *addr, size_t size)
{
    free(addr);
}

static uintptr_t malloc_dma_pin(void *cookie, void *addr, size_t size)
{
    return (uintptr_t)addr;
}

static void malloc_dma_unpin(void *cookie, void *addr, size_t size)
{
}

static void malloc_dma_cache_op(void *cookie, void *addr, size_t size, dma_cache_op_t op)
{
}

void udp_recv_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p, ip_addr_t *ip, u16_t port) {
    printf("Received udp packet of %d bytes from %s:%d\n", p->len, ipaddr_ntoa(ip), port);
    char *data = malloc(p->len + 1);
    strncpy(data, p->payload, p->len);
    data[p->len] = '\0';

    printf("Data: %s\n", data);
    free(data);
    /* send the data back */
    udp_sendto(pcb, p, ip, port);
    pbuf_free(p);
}

void netif_link_callback(struct netif *netif) {
    if (netif_is_link_up(netif)) {
        int err;
        printf("Link is up\n");
        printf("IPADDR is %s\n", ipaddr_ntoa(&netif->ip_addr));
        struct udp_pcb *udp_conn = udp_new();
        ZF_LOGF_IF(!udp_conn, "Failed to create udp connection");

        err = udp_bind(udp_conn, IP_ADDR_ANY, 7);
        ZF_LOGF_IF(err != ERR_OK, "Failed to bind port 7");
        udp_recv(udp_conn, udp_recv_callback, NULL);
    }
}

static struct netif *init_interface(lwip_iface_t *lwip) {
    assert(lwip->netif == NULL);
    struct netif *netif = malloc(sizeof(*netif));
    err_t err;
    ip_addr_t addr, mask, gw;
    IP4_ADDR(&mask, 255,255,255,0);
    IP4_ADDR(&gw, 192,168,168,1);
    IP4_ADDR(&addr, 192,168,168,2);

    /* Initialise after configuration */
    lwip->netif = netif_add(netif, &addr, &mask, &gw, lwip,  ethif_get_ethif_init(lwip), ethernet_input);

    assert(lwip->netif != NULL);
    netif_set_default(lwip->netif);
    netif_set_status_callback(lwip->netif, netif_link_callback);
    netif_set_link_up(lwip->netif);
    netif_set_up(netif);
    // err = dhcp_start(lwip->netif);
    // ZF_LOGF_IF(err != ERR_OK, "Failed to start dhcp");

    return netif;
}

static ps_io_ops_t io_ops;

void eth_init()
{
    memset(&io_ops, 0, sizeof(io_ops));
    io_ops.dma_manager = (ps_dma_man_t) {
        .cookie = NULL,
        .dma_alloc_fn = malloc_dma_alloc,
        .dma_free_fn = malloc_dma_free,
        .dma_pin_fn = malloc_dma_pin,
        .dma_unpin_fn = malloc_dma_unpin,
        .dma_cache_op_fn = malloc_dma_cache_op
    };

    /* Create a driver. This utilises preallocated buffers, backed up by malloc above */
    if (NULL == ethif_new_lwip_driver_no_malloc(io_ops, NULL, ethdriver_init, NULL, &lwip_driver)) {
        ZF_LOGF("Failed to create the lwip Driver");
    } 

    /* Initialise LWIP stack */
    lwip_init();

    // lwip iface
    struct netif *iface = init_interface(&lwip_driver);
    if (iface == NULL) {
        ZF_LOGF("Failed to create the lwip interface");
    }
}
