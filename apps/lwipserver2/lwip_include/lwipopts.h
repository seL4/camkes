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

#pragma once

#define NO_SYS                          1
#define NO_SYS_NO_TIMERS                0
#define LWIP_TIMERS                     1
#define LWIP_NETCONN                    0
#define LWIP_SOCKET                     0
#define LWIP_IGMP                       1
#define LWIP_RAND                       rand
#define LWIP_DHCP                       1

#define MEM_ALIGNMENT 4
#define MEM_SIZE                        0x40000

#define ETHARP_SUPPORT_STATIC_ENTRIES   1
#define SYS_LIGHTWEIGHT_PROT            0
#define LWIP_NETIF_STATUS_CALLBACK      1

#define TCP_SND_QUEUELEN 2500
#define MEMP_NUM_TCP_SEG TCP_SND_QUEUELEN
#define TCP_SND_BUF (100 * TCP_MSS)
#define TCP_WND (100 * TCP_MSS)
#define LWIP_WND_SCALE 1
#define TCP_RCV_SCALE 10
#define PBUF_POOL_SIZE 1000
#define MEMP_NUM_SYS_TIMEOUT 512

/* Set this to 0 for performance */
#define LWIP_STATS 0

/* Debugging options */
#define LWIP_DEBUG
/* Change this to LWIP_DBG_LEVEL_ALL to see a trace */
#define LWIP_DBG_MIN_LEVEL              LWIP_DBG_LEVEL_WARNING

#define ETHARP_DEBUG                    LWIP_DBG_ON
#define PBUF_DEBUG                      LWIP_DBG_ON
#define IP_DEBUG                        LWIP_DBG_ON
#define TCPIP_DEBUG                     LWIP_DBG_ON
#define DHCP_DEBUG                      LWIP_DBG_ON
#define UDP_DEBUG                       LWIP_DBG_ON
