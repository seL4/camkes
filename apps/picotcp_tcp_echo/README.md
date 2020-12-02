<!--
     Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)

     SPDX-License-Identifier: BSD-2-Clause
-->

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
total,58777271911
idle,0
kernel,923710938
{
  "BENCHMARK_TOTAL_UTILISATION":58777271911,
  "BENCHMARK_TOTAL_KERNEL_UTILISATION":923710938,
  "BENCHMARK_TOTAL_NUMBER_KERNEL_ENTRIES":1837568,
  "BENCHMARK_TOTAL_NUMBER_SCHEDULES":273465,
  "BENCHMARK_TCB_": [
    {
      "NAME":"time_server:the_timer",
      "UTILISATION":14049847,
      "NUMBER_SCHEDULES":5560,
      "KERNEL_UTILISATION":6403362,
      "NUMBER_KERNEL_ENTRIES":5560
    },
    {
      "NAME":"time_server:nv_timer",
      "UTILISATION":63687333,
      "NUMBER_SCHEDULES":6810,
      "KERNEL_UTILISATION":10281140,
      "NUMBER_KERNEL_ENTRIES":17053
    },
    {
      "NAME":"time_server:control",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"serial_server:serial_dev",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"serial_server:processed_putchar",
      "UTILISATION":47813649,
      "NUMBER_SCHEDULES":7334,
      "KERNEL_UTILISATION":5789123,
      "NUMBER_KERNEL_ENTRIES":8550
    },
    {
      "NAME":"serial_server:control",
      "UTILISATION":170729,
      "NUMBER_SCHEDULES":111,
      "KERNEL_UTILISATION":95688,
      "NUMBER_KERNEL_ENTRIES":222
    },
    {
      "NAME":"reset_server:control",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"picoserver:trace_stop",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"picoserver:trace_start",
      "UTILISATION":1994,
      "NUMBER_SCHEDULES":1,
      "KERNEL_UTILISATION":938,
      "NUMBER_KERNEL_ENTRIES":1
    },
    {
      "NAME":"picoserver:control",
      "UTILISATION":48985408582,
      "NUMBER_SCHEDULES":136881,
      "KERNEL_UTILISATION":164628654,
      "NUMBER_KERNEL_ENTRIES":260965
    },
    {
      "NAME":"gpiomux_server:mux",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"gpiomux_server:gpio",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"gpiomux_server:control",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"ethdriver:trace_stop",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"ethdriver:trace_start",
      "UTILISATION":2479,
      "NUMBER_SCHEDULES":1,
      "KERNEL_UTILISATION":1395,
      "NUMBER_KERNEL_ENTRIES":1
    },
    {
      "NAME":"ethdriver:control",
      "UTILISATION":3728117922,
      "NUMBER_SCHEDULES":46063,
      "KERNEL_UTILISATION":661280085,
      "NUMBER_KERNEL_ENTRIES":1474493
    },
    {
      "NAME":"eth0d1:control",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"eth0d0:control",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"echod1:control",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"echod0:control",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"echo:trace_stop",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"echo:trace_start",
      "UTILISATION":2381,
      "NUMBER_SCHEDULES":1,
      "KERNEL_UTILISATION":1029,
      "NUMBER_KERNEL_ENTRIES":1
    },
    {
      "NAME":"echo:control",
      "UTILISATION":190169008,
      "NUMBER_SCHEDULES":66134,
      "KERNEL_UTILISATION":72441168,
      "NUMBER_KERNEL_ENTRIES":66154
    },
    {
      "NAME":"clock_server:car",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"clock_server:control",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"bpmp_server:hsp",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"bpmp_server:control",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"bench:idle",
      "UTILISATION":3220,
      "NUMBER_SCHEDULES":2,
      "KERNEL_UTILISATION":1609,
      "NUMBER_KERNEL_ENTRIES":2
    },
    {
      "NAME":"bench:bench_to",
      "UTILISATION":5747844767,
      "NUMBER_SCHEDULES":4566,
      "KERNEL_UTILISATION":2786747,
      "NUMBER_KERNEL_ENTRIES":4566
    },
    {
      "NAME":"bench:control",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"idle_thread",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":1,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    },
    {
      "NAME":"rootserver",
      "UTILISATION":0,
      "NUMBER_SCHEDULES":0,
      "KERNEL_UTILISATION":0,
      "NUMBER_KERNEL_ENTRIES":0
    }
  ]
}
traces:ethdriver
total_endpoint_calls,143519
cycles,942968
total_notifications,143519
cycles,4015637001
irq_handlers,124985
cycles,1439198942
tx_event,37278
cycles,2563376277
rx_buffers_available_event,0
cycles,0
notify_client,143519
cycles,2893493
traces:picoserver
total_endpoint_calls,116020
cycles,1412327
total_notifications,116009
cycles,48968713983
irq_handlers,0
cycles,1273829
ethernet_event_handler,44405
cycles,44360278745
client_event_handler,66045
cycles,4157066253
notify_ethernet,116009
cycles,3796540
pico_server_tick,5559
cycles,372728925
notify_client,116009
cycles,62344453
traces:echo
total_endpoint_calls,66048
cycles,422112
total_notifications,66048
cycles,102229239
irq_handlers,0
cycles,3283110
async_notification,66045
cycles,90497677
sync_notification,3
cycles,4516750
echo: Connection established with 10.13.1.11 on socket 3
```
