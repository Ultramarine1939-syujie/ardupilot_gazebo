### Long Commands

位置控制基本属于长命令调用模块，该模块调用方法如下：

```
module load cmdlong
```

#### 飞行器控制

1、如果处于自动飞行模式，请将飞行器目标速度设置为`N`m/s

```
setspeed N
```

2、将车辆的目标偏航设置为`ANGLE`（0-360），最大角速度为`ANGULAR_SPEED`（度/秒）。`MODE`为 0（绝对角度）或 1（相对角度）

```
setyaw ANGLE ANGULAR_SPEED MODE
```

3、向车辆发送自动起飞命令。它将认为起飞在 `ALTITUDE_IN_METERS`（相对）完成

```
takeoff ALTITUDE_IN_METERS
```

4、在local north-east-down (x, y, z)坐标系中设置所需的车辆速度。所有速度均以 米/秒 为单位

```
velocity X Y Z
```

5、在local north-east-down (x, y, z)坐标系中设置所需的车辆位置。所有位置以 m 为单位

```
position X Y Z
```

6、以四元数格式设置所需的姿态

```
attitude Q0 Q1 Q2 Q3 thrust
```

7、根据上一次鼠标在地图上的单击以及以 North-East-Down 格式 (m/s) 表示的目标速度设置目标位置。使用全局框架。

```
posvel N E D
```

#### 系统控制

向车辆发送通用 MAV_CMD_LONG 消息。`COMMAND`是命令的名称。选项遵循格式。`[arg1] [arg2] ...`

```
cmdlong COMMAND OPTIONS
```



### Auxiliary (RC 7 and 8) Options

```
module load auxopt
```

允许用户更改映射到RC上的辅助通道 7 和 8 的操作。

使用和分别显示 RC 通道的可用操作列表及其当前设置。`auxopt list` `auxopt show`

使用和分别设置和重置映射到 RC 通道的操作。`auxopt set [ch] [action]` `auxopt reset`



### Parma参数设置

| **Command**    | **Description**                                       |
| -------------- | ----------------------------------------------------- |
| param show X   | Show current value of parameter X                     |
| param set X N  | Set parameter X to value N                            |
| param download | Download parameter definitions from ArduPilot website |
| param help X   | Display definition of parameter X                     |
