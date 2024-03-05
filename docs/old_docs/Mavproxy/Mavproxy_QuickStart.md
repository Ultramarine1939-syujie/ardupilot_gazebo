### Mavproxy_QuickStart

#### Over USB

If there is only 1 autopilot connected and it does not present multiple ports (CAN enabled devices present two ports), the `--master` is not required. MAVProxy will autodetect the correct port.

```
mavproxy.py --master=/dev/ttyUSB0
```

Normally MAVProxy will auto-detect the correct baudrate. If required, the baud rate can instead be manually specified.

```
mavproxy.py --master=/dev/ttyUSB0 --baudrate=57600
```

#### Over Network

Specify the IP address and port containing a mavlink stream. The address to connect to must be your own IP address or loopback address. Alternatively, if the local IP address is not known, use 0.0.0.0 for MAVProxy find and use the local IP address. The type of stream (tcp or udp) should also be specified.

```
mavproxy.py --master=tcp:192.168.1.1:14550
mavproxy.py --master=udp:127.0.0.1:14550
mavproxy.py --master=tcp:0.0.0.0:14550
```

If connecting to a remote IP address, the udpout or tcpout arguments should be used:

```
mavproxy.py --master=udpout:10.10.1.1:14550
mavproxy.py --master=tcpout:10.10.1.1:14550
```

### Useful Param

#### --baudrate

Specify baudrate of `--master` and `--out` ports. Only applicable for serial links.

#### --console

Load the GUI console module on startup. 

#### --map

Load the moving map module on startup. 

#### --load-module

Load the specified module on startup. Can be used multiple times, or with a comma separated list. 

#### --mavversion

Specify MAVLink version. Can be 1.0 or 2.0. Otherwise MAVProxy will autodetect the MAVLink version