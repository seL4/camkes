/*
 * Copyright 2020, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#include <autoconf.h>
#include <stdbool.h>

#include <camkes.h>
#include <camkes/dma.h>
#include <camkes/io.h>
#include <camkes/irq.h>

#include <platsupport/io.h>
#include <platsupport/irq.h>
#include <ethdrivers/raw.h>
#include <sel4utils/sel4_zf_logif.h>

#undef PACKED
#include <pico_stack.h>
#include <pico_socket.h>
#include <pico_addressing.h>
#include <pico_ipv4.h>
#include <pico_dhcp_client.h>
#include <pico_device.h>

#include "tuning_params.h"


struct eth_driver *eth_driver;

struct pico_device pico_dev;

/*
 *Struct eth_buf contains a virtual address (buf) to use for memory operations
 *at the picoserver level and a physical address to be passed down to the
 *driver.
 */
typedef struct eth_buf {
    char *buf;
    uintptr_t phys;
    size_t len;
} eth_buf_t;

eth_buf_t rx_bufs[RX_BUFS];
eth_buf_t tx_bufs[TX_BUFS];

/* keeps track of the head of the queue */
int pending_rx_head;
/* keeps track of the tail of the queue */
int pending_rx_tail;

/*
 * this is a cyclic queue of RX buffers pending to be read by a client,
 * the head represents the first buffer in the queue, and the tail the last
 */
eth_buf_t *pending_rx[RX_BUFS];

/* keeps track of how many TX buffers are in use */
int num_tx;
/*
 * this represents the pool of buffers that can be used for TX,
 * this array is a sliding array in that num_tx acts a pointer to
 * separate between buffers that are in use and buffers that are
 * not in use. E.g. 'o' = free, 'x' = in use
 *  -------------------------------------
 *  | o | o | o | o | o | o | x | x | x |
 *  -------------------------------------
 *                          ^
 *                        num_tx
 */
eth_buf_t *tx_buf_pool[TX_BUFS];


static int num_rx_bufs;
static eth_buf_t *rx_buf_pool[RX_BUFS];

static void eth_tx_complete(void *iface, void *cookie)
{
    eth_buf_t *buf = (eth_buf_t *)cookie;
    tx_buf_pool[num_tx] = buf;
    num_tx++;
}

static uintptr_t eth_allocate_rx_buf(void *iface, size_t buf_size, void **cookie)
{
    if (buf_size > BUF_SIZE) {
        return 0;
    }
    if (num_rx_bufs == 0) {
        return 0;
    }
    num_rx_bufs--;
    *cookie = rx_buf_pool[num_rx_bufs];
    return rx_buf_pool[num_rx_bufs]->phys;
}


static void eth_rx_complete(void *iface, unsigned int num_bufs, void **cookies, unsigned int *lens)
{
    /* insert filtering here. currently everything just goes to one client */
    if (num_bufs != 1) {
        goto error;
    }
    eth_buf_t *curr_buf = cookies[0];
    if (((pending_rx_head + 1) % RX_BUFS) == pending_rx_tail) {
        goto error;
    }
    curr_buf->len = lens[0];
    pending_rx[pending_rx_head] = curr_buf;
    pending_rx_head = (pending_rx_head + 1) % RX_BUFS;
    return;
error:
    /* abort and put all the bufs back */
    for (int i = 0; i < num_bufs; i++) {
        eth_buf_t *returned_buf = cookies[i];
        rx_buf_pool[num_rx_bufs] = returned_buf;
        num_rx_bufs++;
    }
}

static struct raw_iface_callbacks ethdriver_callbacks = {
    .tx_complete = eth_tx_complete,
    .rx_complete = eth_rx_complete,
    .allocate_rx_buf = eth_allocate_rx_buf
};


/* Async driver will set a flag to signal that there is work to be done  */
static int pico_eth_poll(struct pico_device *dev, int loop_score)
{
    while (loop_score > 0) {
        int err;
        if (pending_rx_head == pending_rx_tail) {
            break;
        }
        eth_buf_t *rx = pending_rx[pending_rx_tail];
        err = pico_stack_recv(dev, (void *)rx->buf, rx->len);
        if (err <= 0) {
            break;
        } else {
            pending_rx_tail = (pending_rx_tail + 1) % RX_BUFS;
            rx_buf_pool[num_rx_bufs] = rx;
            num_rx_bufs++;
        }
        loop_score--;
    }
    if (loop_score == 0) {
        ZF_LOGE("rx loop score died\n");
    }

    return loop_score;
}

static int pico_eth_send(struct pico_device *dev, void *input_buf, int len)
{
    assert(len >= 12);
    if (len > BUF_SIZE || len < 0) {
        ZF_LOGF("Len invalid\n");
    }

    if (num_tx == 0) {
        // No packets available
        return 0; // Error for PICO
    }

    num_tx --;
    eth_buf_t *tx_buf = tx_buf_pool[num_tx];

    /* copy the packet over */
    memcpy(tx_buf->buf, input_buf, len);

    /* queue up transmit */
    int err = eth_driver->i_fn.raw_tx(eth_driver, 1, (uintptr_t *) & (tx_buf->phys),
                                      (unsigned int *)&len, tx_buf);
    switch (err) {
    case ETHIF_TX_FAILED:
        tx_buf_pool[num_tx] = tx_buf;
        num_tx++;
        return 0; // Error for PICO
    case ETHIF_TX_COMPLETE:
    case ETHIF_TX_ENQUEUED:
        break;
    }
    return len;
}




static void tick_on_event(UNUSED seL4_Word badge, void *cookie)
{
    pico_stack_tick();
}

static int hardware_interface_searcher(void *cookie, void *interface_instance, char **properties)
{

    eth_driver = interface_instance;
    return PS_INTERFACE_FOUND_MATCH;
}


int setup_eth0(ps_io_ops_t *io_ops)
{
    int error = ps_interface_find(&io_ops->interface_registration_ops,
                                  PS_ETHERNET_INTERFACE, hardware_interface_searcher, NULL);
    if (error) {
        ZF_LOGE("Unable to find an ethernet device");
        return -1;
    }

    /* preallocate buffers */
    for (int i = 0; i < RX_BUFS; i++) {
        eth_buf_t *buf = &rx_bufs[i];
        buf->buf = ps_dma_alloc(&io_ops->dma_manager, BUF_SIZE, 64, 1, PS_MEM_NORMAL);
        if (!buf) {
            ZF_LOGE("Failed to allocate RX buffer.");
            return -1;
        }
        memset(buf->buf, 0, BUF_SIZE);
        buf->phys = ps_dma_pin(&io_ops->dma_manager, buf->buf, BUF_SIZE);
        if (!buf->phys) {
            ZF_LOGE("ps_dma_pin: Failed to return physical address.");
            return -1;
        }
        rx_buf_pool[num_rx_bufs] = buf;
        num_rx_bufs++;
    }

    for (int i = 0; i < TX_BUFS; i++) {
        eth_buf_t *buf = &tx_bufs[i];
        buf->buf = ps_dma_alloc(&io_ops->dma_manager, BUF_SIZE, 64, 1, PS_MEM_NORMAL);
        if (!buf) {
            ZF_LOGE("Failed to allocate TX buffer: %d.", i);
            return -1;
        }
        memset(buf->buf, 0, BUF_SIZE);
        buf->phys = ps_dma_pin(&io_ops->dma_manager, buf->buf, BUF_SIZE);
        if (!buf->phys) {
            ZF_LOGE("ps_dma_pin: Failed to return physical address.");
            return -1;
        }
        tx_buf_pool[num_tx] = buf;
        num_tx++;
    }

    /* Setup ethdriver callbacks and poll the driver so it can do any more init. */
    eth_driver->cb_cookie = NULL;
    eth_driver->i_cb = ethdriver_callbacks;
    eth_driver->i_fn.raw_poll(eth_driver);

    /* Setup pico device to install into picotcp */
    pico_dev.send = pico_eth_send;
    pico_dev.poll = pico_eth_poll;
    uint8_t mac[6] = {0};
    eth_driver->i_fn.get_mac(eth_driver, mac);
    pico_dev.mtu = 1500;
    if (pico_device_init(&pico_dev, "eth0", mac) != 0) {
        ZF_LOGF("Failed to initialize pico device");
    }
    /* Set a maximum number of frames in the device queue to avoid memory leaks. */
    pico_dev.q_in->max_frames = 512;
    pico_dev.q_out->max_frames = 512;

    single_threaded_component_register_handler(0, "pico_stack_tick", tick_on_event, NULL);

    return 0;
}

CAMKES_POST_INIT_MODULE_DEFINE(install_eth_device, setup_eth0);
