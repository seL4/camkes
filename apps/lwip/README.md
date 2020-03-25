# LWIP app

LWIP echo server with any luck, based off the picoserver

## Troubleshooting

### ping doesn't work

Try ```arpping```

```bash
arpping -i eth0 192.168.168.2
```

You should see many packets going back and forth

If there are none check that you are servicing lwip in your timer interrupt.

### arp ping only returns one packet

```bash
arpping -i eth0 192.168.168.2
```

try pinging broadcast

```bash
arpping -b -i eth0 192.168.168.2
```

if this works it is likely you have different mac addresses for your hardware and lwip stack.
