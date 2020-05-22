# Picotcp echo server example

This echo server listens on 3 ports:
- TCP echo on port 1234
- UDP echo on port 1235
- Utilization on port 1236

Currently 2 platforms are supported:
- x86_64 with an e1000 82574 ethernet card
- NVIDIA Jetson TX2

Each platform has a separate CAmkES ADL file.


## Benchmarking

### IPBench

This app and picotcp_single_component can be used with ipbench (http://ipbench.sourceforge.net/)
to measure throughput and latency stastics under different usage profiles.

### Tracing

Some of the components in this example can have their behavior traced.
Adding a connection to a benchmarking component like shown here will cause
component tracepoints to be reset and printed alongside utilization measurements.
More information about the format of the results is below.
```
        BenchUtiliz_trace_connections(trace, picoserver, bench)
```

### Utilization TCP endpoint

This application has a TCP socket listening on port 1236 that returns system utilization
information using an ipbench protocol enumerated below.

When the listner receives START it starts measuring utilization statistics.
When the listener receives STOP it stops measuring utilization statistics and returns the
system utilization. This is measured with a user level IDLE thread.  The result returned
is the IDLE thread's measured utilization % subtracted from 1.  So if the IDLE thread hasn't
run then the value returned will be 1 and if only the IDLE thread has run 0.000 will be returned.
```
kentm@viscous:~$ nc 10.13.1.74 1236
100 IPBENCH V1.0
HELLO
200 OK (Ready to go)
LOAD cpu_target_lukem
200 OK
SETUP args::""
200 OK
START
STOP
220 VALID DATA (Data to follow)
Content-length: 6
0.002

```

In addition, more usage statistics will be printed using the terminal. The output
first lists cycle counts for every thread in the system and total cycle counts spent
in the kernel.
Traces for single threaded components will be dumped next. The format of these results
are the name of the event followed by the number of times the event was fired, followed
by the total number of cycles spent processing the event.

```
Measurment starting...
total,78102218484
idle,0
kernel,12270142352
time_server:the_timer,11268012
time_server:irq,82311844
time_server:control,0
picoserver:trace_stop,0
picoserver:trace_start,4692
picoserver:control,34194373852
ethdriver:trace_stop,0
ethdriver:trace_start,4628
ethdriver:control,19372539412
eth0d1:control,0
eth0d0:control,0
echod1:control,0
echod0:control,0
echo:control,9369350484
bench:idle,5788
bench:bench_to,15072359772
bench:control,0
idle_thread,0
rootserver,0
idle/tot: 13072357732/78102216864, idle proportion: 16.737499%
traces,ethdriver
total_endpoint_calls,0,0
total_notifications,2456368,9698950480
irq_handlers,814947,5025007380
tx_event,1641435,1246216948
rx_buffers_available_event,0,0
notify_client,2456368,2727686084
traces,picoserver
total_endpoint_calls,11,11924
total_notifications,3297942,21756933268
irq_handlers,0,182479780
ethernet_event_handler,1666462,7509043892
notify_ethecho: Connection closed on socket 0x4c
ernet,3297943,2835136012
pico_server_tick,2368,26574836
client_event_handler,1641489,6828125924
notify_client,3297946,2885003836
echo: Connection established with 10.13.1.11 on socket 3
```
