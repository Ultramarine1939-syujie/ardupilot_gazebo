# Mavproxy使用教程

#### 连接飞行器

**有线连接**

```shell
mavproxy.py --master=/dev/ttyUSB0 --baudrate=57600
```

**无线连接**

```shell
#use 0.0.0.0 for MAVProxy find and use the local IP address. 
mavproxy.py --master=tcp:192.168.1.1:14550
mavproxy.py --master=udp:127.0.0.1:14550
mavproxy.py --master=tcp:0.0.0.0:14550
#If connecting to a remote IP address, the udpout or tcpout arguments should be used:
mavproxy.py --master=udpout:10.10.1.1:14550
mavproxy.py --master=tcpout:10.10.1.1:14550
```

#### 飞行模式（必需）

```
mode	#切换模式

#Available modes:  
dict_keys(['STABILIZE', 'ACRO', 'ALT_HOLD', 'AUTO', 'GUIDED', 'LOITER', 'RTL', 'CIRCLE', 'POSITION', 'LAND', 'OF_LOITER', 'DRIFT', 'SPORT', 'FLIP', 'AUTOTUNE', 'POSHOLD', 'BRAKE', 'THROW', 'AVOID_ADSB', 'GUIDED_NOGPS', 'SMART_RTL', 'FLOWHOLD', 'FOLLOW', 'ZIGZAG', 'SYSTEMID', 'AUTOROTATE', 'AUTO_RTL'])
```

#### 解锁（必需）

```
arm throttle			#解锁
arm throttle force		#强制解锁
```

#### 上锁

```
disarm				#上锁
disarm force		#强制上锁
```

#### 安全开关

```
arm safetyon		#启动开关
arm safetyoff		#关闭开关
```

#### 解锁检查

参数可以是以下内容：all, baro, compass, gps, ins, params, rc, voltage, battery, airspeed, logging, switch, gps_config

```
arm check X			#启用检查
arm uncheck X		#禁用检查	#（SITL必需）
```

#### 传感器校准

```
accelcal			#加速度
accelcalsimple		#简单加速度
gyrocal				#陀螺仪
calpress			#气压计
compassmot			#启动磁力计/电机干扰校准例程
level				#水平
rccal				#RC输入
ground				#全地面模式，包括陀螺仪和压力传感器校准
magcal				#罗盘
ahrstrim			#AHRS
```

#### 系统指令

```
reboot		#重启自驾仪
setup		#进入 APM 的设置 (CLI) 模式
rc			#覆写RC输入通道，该值将保留直至值被设为0.		#rc 1 1000	#rc all 0
time		#显示自动驾驶仪的当前时间,括号内的时间为地面站时间
script		#运行包含 MAVProxy 命令的文本文件
shell		#执行shell命令
status		#显示从自动驾驶仪接收到的最新数据包，取无人机的状态
exit		#退出mavproxy
```

#### 辅助通道设置 Auxiliary (RC 7 and 8) Options

```
module load auxopt
```

允许用户更改映射到RC上的辅助通道 7 和 8 的操作。

使用和分别显示 RC 通道的可用操作列表及其当前设置。`auxopt list` `auxopt show`

使用和分别设置和重置映射到 RC 通道的操作。`auxopt set [ch] [action]` `auxopt reset`

#### 参数修改

| **Command**    | **Description**                                       |
| -------------- | ----------------------------------------------------- |
| param show X   | Show current value of parameter X                     |
| param set X N  | Set parameter X to value N                            |
| param download | Download parameter definitions from ArduPilot website |
| param help X   | Display definition of parameter X                     |

#### 直接控制飞行

位置控制基本属于长命令调用模块，该模块调用方法如下：

```
setspeed N							#飞行器目标速度设置为`N`m/s
setyaw ANGLE ANGULAR_SPEED MODE		#将车辆的目标偏航设置为`ANGLE`（0-360），最大角速度为`ANGULAR_SPEED`（度/秒）。`MODE`为 0（绝对角度）或 1（相对角度）
takeoff ALTITUDE_IN_METERS			#发送自动起飞命令（相对高度）
velocity X Y Z						#在local north-east-down (x, y, z)坐标系中设置所需的车辆速度
position X Y Z						#在local north-east-down (x, y, z)坐标系中设置所需的车辆位置（相对位置）
attitude Q0 Q1 Q2 Q3 thrust			#以四元数格式设置所需的姿态
posvel N E D						#根据上一次鼠标在地图上的单击以及以 North-East-Down 格式 (m/s) 表示的目标速度设置目标位置。
cmdlong COMMAND OPTIONS				#向车辆发送通用 MAV_CMD_LONG 消息。`COMMAND`是命令的名称。选项遵循格式。`[arg1] [arg2] ...`
```

#### 航点飞行

MAVProxy 包含一些用于管理航路点的命令。这些可以通过命令行或 GUI 控制台的菜单栏输入。

```
wp list						#查看已经加载进自驾仪的航点
wp load filename.txt		#加载特定航点文件
wp save filename.txt		#保存当前航点文件
wp clear					#删除已加载的所有航点
wp update filename.txt 6	#加载特定文件的特定航点（与wp load类似但不同）
wp move 6					#将特定航路点移动到新位置，输入后可以在地图上选择新位置
wp loop						#允许自动驾驶仪重复任务
wp remove 0					#从任务中删除特定航点
wp set 	0					#将指定航点作为当前航点。任务将从该路径点开始运行。如果飞控运行在 AUTO 模式，它将立即前往该航路点。
wp undo						#撤销操作，恢复上次航路点更改或编辑
```

#### 地理围栏

地理围栏代表了无人机无法飞越的硬性限制。它对于防止无人机失控（除非出现其他软件/硬件问题）非常有用。如果它突破围栏，故障安全装置将被激活，使其返回原点。

它被表示为固定翼飞行器飞行区域周围航路点的任意多边形。在ArduCopter中，它是代表飞行区域周围的圆柱体的半径和高度参数。

```
fence list					#查看当前加载内容
fence load filename.txt		#加载
fence save filename.txt		#保存
fence draw					#在地图上绘制（显示）地理围栏
fence enable				#启动
fence disable				#禁用
fence clear					#清除
fence move 6				#将特定栅栏坐标移动到新位置。输入后，可以在地图窗口上选择新位置
fence remove 6				#删除特点地理围栏坐标
```

#### 返航点

返航点是 APM 的home列表。进入故障安全模式（且参数设置为返航）后，自动驾驶仪会将无人机飞至最近的返航点。请注意，每个自动驾驶仪最多支持 5 个返航点。

这在长距离飞行中非常有用，无人机返回较近的返航点比一路飞回原始返航点更安全。

```
rally list					#在自动驾驶仪上查看当前加载的返航点
rally load filename.txt		#从文件加载一组新的返航点
rally save filename.txt		#将当前集合点集保存到文件中
rally clear					#从自动驾驶仪中删除返航点
rally move 6				#将特定返航点修改为新位置。输入后，可以在地图窗口上选择新位置
rally add					#添加新的返航点。输入后，可以在地图窗口上选择一个位置
rally remove 6				#删除特定的返航点
rally land					#命令自动驾驶仪从返航点着陆
```

参考：http://diydrones.com/profiles/blogs/landing-from-rally-points

### 