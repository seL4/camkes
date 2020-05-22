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
#include <stdbool.h>

#include <camkes.h>
#include <camkes/dma.h>
#include <camkes/io.h>
#include <camkes/irq.h>

#include <platsupport/io.h>
#include <platsupport/irq.h>
#include <ethdrivers/raw.h>
#include <ethdrivers/intel.h>
#include <sel4utils/sel4_zf_logif.h>

#undef PACKED
#include <pico_stack.h>
#include <pico_socket.h>
#include <pico_addressing.h>
#include <pico_ipv4.h>
#include <pico_dhcp_client.h>
#include <pico_device.h>

#define RX_BUFS 510

#define CLIENT_RX_BUFS 510
#define CLIENT_TX_BUFS 510

#define BUF_SIZE 2048


static struct eth_driver *eth_driver;

struct pico_device pico_dev;

/*
 *Struct eth_buf contains a virtual address (buf) to use for memory operations
 *at the picoserver level and a physical address to be passed down to the
 *driver.
 */
typedef struct eth_buf {
    void *buf;
    uintptr_t phys;
} eth_buf_t;

typedef struct rx_frame {
    eth_buf_t *buf; // Clients share a pool of RX frames
    int len;
    int client;
} rx_frame_t;

typedef struct tx_frame {
    eth_buf_t buf; // Each client has a pool of TX frames
    int len;
    int client;
} tx_frame_t;

typedef struct client {

    /* keeps track of the head of the queue */
    int pending_rx_head;
    /* keeps track of the tail of the queue */
    int pending_rx_tail;
    /*
     * this is a cyclic queue of RX buffers pending to be read by a client,
     * the head represents the first buffer in the queue, and the tail the last
     */
    rx_frame_t pending_rx[CLIENT_RX_BUFS];

    /* keeps track of how many TX buffers are in use */
    int num_tx;
    /* the allocated TX buffers for the client */
    tx_frame_t tx_mem[CLIENT_TX_BUFS];
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
    tx_frame_t *pending_tx[CLIENT_TX_BUFS];


} client_t;

static int num_clients = 0;
static client_t *clients = NULL;

static int num_rx_bufs;
static eth_buf_t rx_bufs[RX_BUFS];
static eth_buf_t *rx_buf_pool[RX_BUFS];


static void eth_tx_complete(void *iface, void *cookie)
{
    tx_frame_t *buf = (tx_frame_t *)cookie;
    client_t *client = &clients[buf->client];
    client->pending_tx[client->num_tx] = buf;
    client->num_tx++;
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

static void give_client_buf(client_t *client, eth_buf_t *buf, unsigned int len)
{
    client->pending_rx[client->pending_rx_head] = (rx_frame_t) {
        buf, len, 0
    };
    client->pending_rx_head = (client->pending_rx_head + 1) % CLIENT_RX_BUFS;
}


static void eth_rx_complete(void *iface, unsigned int num_bufs, void **cookies, unsigned int *lens)
{
    /* insert filtering here. currently everything just goes to one client */
    if (num_bufs != 1) {
        goto error;
    }
    eth_buf_t *curr_buf = cookies[0];
    client_t *client = &clients[0];
    if ((client->pending_rx_head + 1) % CLIENT_RX_BUFS == client->pending_rx_tail) {
        goto error;
    }
    give_client_buf(client, curr_buf, lens[0]);
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
    int len;

    while (loop_score > 0) {
        int ret;
        client_t *client = &clients[0];
        if (client->pending_rx_head == client->pending_rx_tail) {
            break;
        }
        rx_frame_t rx = client->pending_rx[client->pending_rx_tail];
        client->pending_rx_tail = (client->pending_rx_tail + 1) % CLIENT_RX_BUFS;

        pico_stack_recv(dev, (void *)rx.buf->buf, rx.len);

        if (client->pending_rx_tail == client->pending_rx_head) {
            ret = 0;
        } else {
            ret = 1;
        }
        rx_buf_pool[num_rx_bufs] = rx.buf;
        num_rx_bufs++;

        loop_score--;
        if (ret == 0) {
            break;
        }
    }
    if (loop_score == 0) {
        printf("loop score died\n");
    }

    return loop_score;
}


static int pico_eth_send(struct pico_device *dev, void *input_buf, int len)
{
    assert(len >= 12);
    if (len > BUF_SIZE || len < 0) {
        ZF_LOGF("Len invalid\n");
    }
    int err = ETHIF_TX_COMPLETE;
    int id = 0;
    client_t *client = &clients[0];
    assert(client);

    /* silently drop packets */
    if (client->num_tx != 0) {
        client->num_tx --;
        tx_frame_t *tx_buf = client->pending_tx[client->num_tx];

        /* copy the packet over */
        memcpy(tx_buf->buf.buf, input_buf, len);

        /* queue up transmit */
        err = eth_driver->i_fn.raw_tx(eth_driver, 1, (uintptr_t *) & (tx_buf->buf.phys),
                                      (unsigned int *)&len, tx_buf);
        if (err != ETHIF_TX_ENQUEUED) {
            /* Free the internal tx buffer in case tx fails. Up to the client to retry the trasmission */
            client->num_tx++;
        }
    } else {
        return 0; // Error for PICO
    }

    switch (err) {
    case ETHIF_TX_FAILED:
        ZF_LOGE("Failed tx\n");
        return 0; // Error for PICO
    case ETHIF_TX_COMPLETE:
    case ETHIF_TX_ENQUEUED:
        break;
    }
    return len;
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
        ZF_LOGF("Unable to find an ethernet device");
    }

    eth_driver->cb_cookie = NULL;
    eth_driver->i_cb = ethdriver_callbacks;

    /* preallocate buffers */
    for (int i = 0; i < RX_BUFS; i++) {
        void *buf = ps_dma_alloc(&io_ops->dma_manager, BUF_SIZE, 4, 1, PS_MEM_NORMAL);
        ZF_LOGF_IF(buf == NULL, "Could not alloc");
        memset(buf, 0, BUF_SIZE);
        uintptr_t phys = ps_dma_pin(&io_ops->dma_manager, buf, BUF_SIZE);
        rx_bufs[num_rx_bufs] = (eth_buf_t) {
            .buf = buf, .phys = phys
        };
        rx_buf_pool[num_rx_bufs] = &(rx_bufs[num_rx_bufs]);
        num_rx_bufs++;
    }
    num_clients = 1;
    clients = calloc(num_clients, sizeof(client_t));
    for (int client = 0; client < num_clients; client++) {
        for (int i = 0; i < CLIENT_TX_BUFS; i++) {
            void *buf = ps_dma_alloc(&io_ops->dma_manager, BUF_SIZE, 4, 1, PS_MEM_NORMAL);
            ZF_LOGF_IF(buf == NULL, "Could not alloc");
            memset(buf, 0, BUF_SIZE);
            uintptr_t phys = ps_dma_pin(&io_ops->dma_manager, buf, BUF_SIZE);
            tx_frame_t *tx_buf = &clients[client].tx_mem[clients[client].num_tx];
            *tx_buf = (tx_frame_t) {
                .len = BUF_SIZE, .client = client
            };
            tx_buf->buf = (eth_buf_t) {
                .buf = buf, .phys = phys
            };
            clients[client].pending_tx[clients[client].num_tx] = tx_buf;
            clients[client].num_tx++;
        }
    }
    eth_driver->i_fn.raw_poll(eth_driver);

    pico_dev.send = pico_eth_send;
    pico_dev.poll = pico_eth_poll;
    uint8_t mac[6] = {0};
    eth_driver->i_fn.get_mac(eth_driver, mac);
    pico_dev.mtu = 1500;
    if (pico_device_init(&pico_dev, "eth0", mac) != 0) {
        ZF_LOGF("Failed to initialize pico device");
    }

    return 0;
}

CAMKES_POST_INIT_MODULE_DEFINE(install_eth_device, setup_eth0);
char *udp_data_packet[0x1000] ALIGN(0x1000);

void handle_udp_picoserver_notification(uint16_t events, struct pico_socket *s)
{
    int ret = 0;
    char ip_string[16] = {0};
    uint32_t orig;
    uint16_t remote_port;

    if (events & PICO_SOCK_EV_RD) {
        ret = pico_socket_recvfrom(s, udp_data_packet, 1400, &orig, &remote_port);
        if (ret == -1) {
            printf("received -1\n");
            return;
        } else if (ret == 0) {
            printf("received 0\n");
            return;
        }
        int inner_ret = pico_socket_sendto(s, udp_data_packet, ret, &orig, remote_port);
        if (inner_ret == -1) {
            printf("received -1 on send\n");
            return;
        }
        if (inner_ret == 0) {
            printf("received 0\n");
            return;
        }
    }

    if (events & PICO_SOCK_EV_ERR) {
        printf("%s: Error with socket %p, going to die\n", get_instance_name(), s);
    }
}


#define MAX_CLIENTS 5

struct pico_socket *socket_in;
struct pico_socket *connected[MAX_CLIENTS];

char *data_packet[MAX_CLIENTS][0x1000] ALIGN(0x1000);

bool write_pending[MAX_CLIENTS];
int ret_save[MAX_CLIENTS];
int done_save[MAX_CLIENTS];


void handle_tcp_picoserver_notification(uint16_t events, struct pico_socket *s)
{
    int ret = 0;
    char ip_string[16] = {0};
    int client_id = -1;
    if (s != socket_in) {
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (connected[i] == s) {
                client_id = i;
                break;
            }
        }
    }



    if (events & PICO_SOCK_EV_CONN) {
        uint32_t peer_addr;
        uint16_t remote_port;
        int connect_client_id = -1;
        assert(client_id == -1);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (connected[i] == NULL) {
                connect_client_id = i;
                break;
            }
        }
        if (connect_client_id == -1 || connect_client_id == MAX_CLIENTS) {
            printf("Cannot connect new client\n");
        } else {
            connected[connect_client_id] = pico_socket_accept(socket_in, &peer_addr, &remote_port);
            if (connected[connect_client_id] == NULL) {
                ZF_LOGE("error\n");
            }
            write_pending[connect_client_id] = false;
            pico_ipv4_to_string(ip_string, peer_addr);
            printf("%s: Connection established with %s on socket %p\n", get_instance_name(), ip_string, connected);
        }


    }
    if (events & PICO_SOCK_EV_WR && write_pending[client_id]) {
        while (ret_save[client_id] > 0) {
            int inner_ret = pico_socket_send(s, data_packet[client_id] + done_save[client_id], ret_save[client_id]);
            if (inner_ret == -1) {
                printf("received -1 on send\n");
                break;
            }
            if (inner_ret == 0) {
                write_pending[client_id] = true;
                ret_save[client_id] = ret_save[client_id];
                done_save[client_id] = done_save[client_id];

                break;
            } else {
                ret_save[client_id] -= inner_ret;
                done_save[client_id] += inner_ret;
            }
        }
        if (ret_save[client_id] == 0) {
            write_pending[client_id] = false;
            events |= PICO_SOCK_EV_RD;
        }

    }

    if (events & PICO_SOCK_EV_RD) {
        while (!write_pending[client_id]) {
            ret = pico_socket_recv(s, data_packet[client_id], 1200);
            if (ret == -1) {
                printf("received -1\n");
                break;
            } else if (ret == 0) {
                break;
            }
            int done = 0;
            while (ret > 0) {
                int inner_ret = pico_socket_send(s, data_packet[client_id] + done, ret);
                if (inner_ret == -1) {
                    printf("received -1 on send\n");
                    break;
                }
                if (inner_ret == 0) {
                    write_pending[client_id] = true;
                    ret_save[client_id] = ret;
                    done_save[client_id] = done;

                    break;
                } else {
                    ret -= inner_ret;
                    done += inner_ret;
                }
            }
        }

    }

    if (events & PICO_SOCK_EV_CLOSE) {
        ret = pico_socket_shutdown(s, PICO_SHUT_RDWR);
        printf("%s: Connection closing on socket %p\n", get_instance_name(), s);
    }
    if (events & PICO_SOCK_EV_FIN) {
        assert(client_id != -1);
        connected[client_id] = NULL;
        printf("%s: Connection closed on socket %p\n", get_instance_name(), s);
    }
    if (events & PICO_SOCK_EV_ERR) {
        printf("%s: Error with socket %p, going to die\n", get_instance_name(), s);
        assert(0);
    }
}


static void tick_on_event(UNUSED seL4_Word badge, void *cookie)
{
    pico_stack_tick();
}


int setup_echo_server(ps_io_ops_t *io_ops)
{

    // TCP echo on port 1234
    socket_in = pico_socket_open(PICO_PROTO_IPV4, PICO_PROTO_TCP, handle_tcp_picoserver_notification);
    if (socket_in == NULL) {
        assert(!"Failed to open a socket for listening!");
    }
    uint32_t local_addr = PICO_IPV4_INADDR_ANY;
    uint16_t port = short_be(1234);
    int ret = pico_socket_bind(socket_in, &local_addr, &port);
    if (ret) {
        ZF_LOGF("Failed to bind a socket for listening: %d!", pico_err);
    } else {
        printf("Bound to addr: %d, port %d\n", local_addr, port);
    }

    ret = pico_socket_listen(socket_in, 1);
    if (ret) {
        assert(!"Failed to listen for incoming connections!");
    }


    // UDP echo on port 1235
    struct pico_socket *udp_socket = pico_socket_open(PICO_PROTO_IPV4, PICO_PROTO_UDP, handle_udp_picoserver_notification);
    if (udp_socket == NULL) {
        assert(!"Failed to open a socket for listening!");
    }
    uint16_t udp_port = short_be(1235);
    ret = pico_socket_bind(udp_socket, &local_addr, &udp_port);
    if (ret) {
        ZF_LOGF("Failed to bind a socket for listening: %d!", pico_err);
    } else {
        printf("Bound to addr: %d, port %d\n", local_addr, udp_port);
    }


    single_threaded_component_register_handler(0, tick_on_event, NULL);
    return 0;

}

CAMKES_POST_INIT_MODULE_DEFINE(setup_sockets, setup_echo_server);

