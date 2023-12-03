### 操作方法

1.在 QGC Mavlink 控制台中执行以下命令：

```
mavlink stream -d /dev/ttyS1 -s HIGHRES_IMU -r 100
mavlink stream -d /dev/ttyS1 -s ATTITUDE_QUATERNION -r 100
```

2.在终端中(26对应data_raw、31对应data)

```
rosrun mavros mavcmd long 511 26 10000 0 0 0 0 0
rosrun mavros mavcmd long 511 31 10000 0 0 0 0 0
```

3、直接修改参数：https://ardupilot.org/dev/docs/mavlink-requesting-data.html

### 来源：

#### 1、mavcmd

```
usage: mavcmd [-h] [-n MAVROS_NS] [-v] [--wait]
              {long,int,sethome,takeoff,land,takeoffcur,landcur,trigger_control}
              ...

Commad line tool for sending commands to MAVLink device.

positional arguments:
  {long,int,sethome,takeoff,land,takeoffcur,landcur,trigger_control}
    long                Send any command (COMMAND_LONG)
    int                 Send any command (COMMAND_INT)
    sethome             Request change home position
    takeoff             Request takeoff
    land                Request land
    takeoffcur          Request takeoff from current GPS coordinates
    landcur             Request land on current GPS coordinates
    trigger_control     Control onboard camera trigerring system (PX4)

optional arguments:
  -h, --help            show this help message and exit
  -n MAVROS_NS, --mavros-ns MAVROS_NS
                        ROS node namespace
  -v, --verbose         verbose output
  --wait                Wait for establishing FCU connection
```

#### 2、COMMAND_LONG

[[Message\] ](https://mavlink.io/zh/messages/common.html#messages)Send a command with up to seven parameters to the MAV. The command microservice is documented at https://mavlink.io/en/services/command.html

| Field Name       | Type     | Values                                                       | Description                                                  |
| ---------------- | -------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| target_system    | uint8_t  |                                                              | System which should execute the command                      |
| target_component | uint8_t  |                                                              | Component which should execute the command, 0 for all components |
| command          | uint16_t | [MAV_CMD](https://mavlink.io/zh/messages/common.html#MAV_CMD) | Command ID (of command to send).                             |
| confirmation     | uint8_t  |                                                              | 0: First transmission of this command. 1-255: Confirmation transmissions (e.g. for kill command) |
| param1           | float    |                                                              | Parameter 1 (for the specific command).                      |
| param2           | float    |                                                              | Parameter 2 (for the specific command).                      |
| param3           | float    |                                                              | Parameter 3 (for the specific command).                      |
| param4           | float    |                                                              | Parameter 4 (for the specific command).                      |
| param5           | float    |                                                              | Parameter 5 (for the specific command).                      |
| param6           | float    |                                                              | Parameter 6 (for the specific command).                      |
| param7           | float    |                                                              | Parameter 7 (for the specific command).                      |

#### 3、MAVLink Commands (MAV_CMD)

Commands to be executed by the MAV. They can be executed on user request, or as part of a mission script. If the action is used in a mission, the parameter mapping to the waypoint/mission message is as follows: Param 1, Param 2, Param 3, Param 4, X: Param 5, Y:Param 6, Z:Param 7. This command list is similar what ARINC 424 is for commercial aircraft: A data format how to interpret waypoint/mission data. NaN and INT32_MAX may be used in float/integer params (respectively) to indicate optional/default values (e.g. to use the component's current yaw or latitude rather than a specific value). See https://mavlink.io/en/guide/xml_schema.html#MAV_CMD for information about the structure of the [MAV_CMD](https://mavlink.io/zh/messages/common.html#mav_commands) entries

#### 4、 MAV_CMD_SET_MESSAGE_INTERVAL ([511](https://mavlink.io/en/messages/common.html#MAV_CMD_SET_MESSAGE_INTERVAL) )

[[Command\] ](https://mavlink.io/en/messages/common.html#mav_commands)Set the interval between messages for a particular MAVLink message ID. This interface replaces [REQUEST_DATA_STREAM](https://mavlink.io/en/messages/common.html#REQUEST_DATA_STREAM).

| Param (:Label)     | Description                                                  | Values                               | Units |
| ------------------ | ------------------------------------------------------------ | ------------------------------------ | ----- |
| 1: Message ID      | The MAVLink message ID                                       | *min:*0 *max:*16777215 *increment:*1 |       |
| 2: Interval        | The interval between two messages. -1: disable. 0: request default rate (which may be zero). | *min:* -1 *increment:*1              | us    |
| 7: Response Target | Target address of message stream (if message has target address fields). 0: Flight-stack default (recommended), 1: address of requestor, 2: broadcast. | *min:*0 *max:*2 *increment:*1        |       |

#### 5、 SCALED_IMU ([ #26 ](https://mavlink.io/en/messages/common.html#SCALED_IMU))

#### 6、 ATTITUDE_QUATERNION ([ #31 ](https://mavlink.io/en/messages/common.html#ATTITUDE_QUATERNION))