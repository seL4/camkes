# LWIP app

LWIP echo server with any luck, based off the picoserver

## Troubleshooting

### ping doesn't work

Try ```arpping```

```bash
arpping -i eth0 192.168.168.2
```

You should see many packets going back and forth

Check that you have set the interface up [correctly](https://www.nongnu.org/lwip/2_1_x/sys_init.html)

and you can add logging to LWIP to help for example

```C
/* debugging */
#define LWIP_DEBUG                      1
#define NETIF_DEBUG                     LWIP_DBG_ON
#define ICMP_DEBUG                      LWIP_DBG_ON
#define IP_DEBUG                        LWIP_DBG_ON | LWIP_DBG_TRACE
#define RAW_DEBUG                       LWIP_DBG_ON
#define UDP_DEBUG                       LWIP_DBG_ON
#define TCP_DEBUG                       LWIP_DBG_ON
#define INET_DEBUG                      LWIP_DBG_ON
#define ETHARP_DEBUG                    LWIP_DBG_ON
#define TIMERS_DEBUG                    LWIP_DBG_ON
```

### arp ping only returns one packet

```bash
arpping -i eth0 192.168.168.2
```

try pinging broadcast

```bash
arpping -b -i eth0 192.168.168.2
```

if this works it is likely you have different mac addresses for your hardware and lwip stack.
