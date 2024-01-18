MAVProxy-HELP（EN）

```
accelcal        : do 3D accelerometer calibration
accelcalsimple  : do simple accelerometer calibration
adsb            : adsb control
ahrstrim        : do AHRS trim
alias           : command aliases
alllinks        : send command on all links
alt             : show altitude information
arm             : arm motors
attitude        : attitude
auxopt          : select option for aux switches on CH7 and CH8 (ArduCopter only)
bat             : show battery information
batreset        : reset battery remaining
calpress        : calibrate pressure sensors
camctrlmsg      : camctrlmsg
cammsg          : cammsg
cammsg_old      : cammsg_old
canforward      : enable CAN forwarding
capabilities    : fetch autopilot capabilities
changealt       : change target altitude
changealt_abs   : change target absolute altitude
click           : set click location
command_int     : execute mavlink command_int
compassmot      : do compass/motor interference calibration
confirm         : confirm a command
console         : console module
corrupt_params  : corrupt param storage
deadlock        : trigger deadlock
devid           : show device names from parameter IDs
dfu_boot        : boot into DFU mode
disarm          : disarm motors
engine          : engine
fence           : fence item management
flashbootloader : flash bootloader (dangerous)
forcecal        : force calibration save
formatsdcard    : format SD card
ftp             : file transfer
gear            : landing gear control
gethome         : get HOME_POSITION
ground          : do a ground start
guided          : fly to a clicked location on map
gyrocal         : do gyro calibration
hardfault_autopilot : hardfault autopilot
internalerror_autopilot : cause internal error in autopilot
land            : auto land
layout          : window layout management
led             : control board LED
level           : set level on a multicopter
link            : link control
lockup_autopilot : lockup autopilot
log             : log file handling
long            : execute mavlink long command
longloop_autopilot : cause long loop in autopilot
magcal          : magcal
magresetofs     : reset offsets for all compasses
magsetfield     : set expected mag field by field
map             : map control
mode            : mode change
module          : module commands
motortest       : motortest commands
namedvaluefloat : send a NAMED_VALUE_FLOAT
oreoled         : control OreoLEDs
output          : output control
panic_autopilot : panic autopilot
parachute       : parachute
param           : parameter handling
pause           : pause AUTO/GUIDED modes
playtune        : play tune remotely
position        : position
posvel          : posvel
rally           : rally item management
rc              : RC input control
rcbind          : bind RC receiver
reboot          : reboot autopilot
relay           : relay commands
repeat          : repeat a command at regular intervals
reset           : reopen the connection to the MAVLink master
resume          : resume AUTO/GUIDED modes
script          : run a script of MAVProxy commands
scripting       : control onboard scripting
servo           : servo commands
set             : mavproxy settings
setorigin       : set global origin
setspeed        : do_change_speed
setup           : go into setup mode
setyaw          : condition_yaw
shell           : run shell command
signing         : signing control
status          : show status
switch          : flight mode switch control
takeoff         : takeoff
terrain         : terrain control
time            : show autopilot time
tuneopt         : Select option for Tune Pot on Channel 6 (quadcopter only)
up              : adjust pitch trim by up to 5 degrees
vehicle         : vehicle control
velocity        : velocity
version         : fetch autopilot version
watch           : watch a MAVLink pattern
wipe_parameters : wipe autopilot parameters
wp              : waypoint management
```

MAVProxy-HELP（CN）

- accelcal：进行三维加速度计校准。
- accelcalsimple：进行简单的加速度计校准。
- adsb：ADS-B 控制。
- ahrstrim：进行 AHRS 修正。
- alias：命令别名。
- alllinks：将命令发送到所有链接。
- alt：显示高度信息。
- arm：解锁电机。
- attitude：姿态信息。
- auxopt：选择 CH7 和 CH8 上辅助开关的选项（仅适用于 ArduCopter）。
- bat：显示电池信息。
- batreset：重置电池剩余电量。
- calpress：校准气压传感器。
- camctrlmsg：相机控制消息。
- cammsg：相机消息。
- cammsg_old：旧版相机消息。
- canforward：启用 CAN 转发。
- capabilities：获取自动驾驶仪的能力。
- changealt：更改目标高度。
- changealt_abs：更改目标绝对高度。
- click：设置点击位置。
- command_int：执行 MAVLink command_int 命令。
- compassmot：进行罗盘/电机干扰校准。
- confirm：确认命令。
- console：控制台模块。
- corrupt_params：破坏参数存储。
- deadlock：触发死锁。
- devid：从参数 ID 显示设备名称。
- dfu_boot：进入 DFU 模式。
- disarm：锁定电机。
- engine：发动机。
- fence：围栏管理。
- flashbootloader：闪存引导程序（危险）。
- forcecal：强制进行校准保存。
- formatsdcard：格式化 SD 卡。
- ftp：文件传输。
- gear：起落架控制。
- gethome：获取 HOME_POSITION。
- ground：进行地面启动。
- guided：飞往地图上的点击位置。
- gyrocal：进行陀螺仪校准。
- hardfault_autopilot：硬错误自动驾驶仪。
- internalerror_autopilot：导致自动驾驶仪内部错误。
- land：自动着陆。
- layout：窗口布局管理。
- led：控制板 LED。
- level：在多旋翼上设置水平面。
- link：链接控制。
- lockup_autopilot：锁定自动驾驶仪。
- log：日志文件处理。
- long：执行 MAVLink 长命令。
- longloop_autopilot：在自动驾驶仪中引起长循环。
- magcal：进行磁力计校准。
- magresetofs：重置所有罗盘偏移量。
- magsetfield：设置预期的磁场。
- map：地图控制。
- mode：模式更改。
- module：模块命令。
- motortest：电机测试命令。
- namedvaluefloat：发送 NAMED_VALUE_FLOAT。
- oreoled：控制 OreoLED。
- output：输出控制。
- panic_autopilot：自动驾驶仪紧急情况。
- parachute：降落伞。
- param：参数处理。
- pause：暂停 AUTO/GUIDED 模式。
- playtune：远程播放音乐。
- position：位置信息。
- posvel：posvel。
- rally：集结点管理。
- rc：RC 输入控制。
- rcbind：绑定 RC 接收器。
- reboot：重新启动自动驾驶仪。
- relay：继电器命令。
- repeat：定期重复命令。
- reset：重新打开与 MAVLink 主机的连接。
- resume：恢复 AUTO/GUIDED 模式。
- script：运行 MAVProxy 命令脚本。
- scripting：控制板上的脚本。
- servo：舵机命令。
- set：Mavproxy设置。
- setorigin：设置全局原点。
- setspeed：do_change_speed。
- setup：进入设置模式。
- setyaw：condition_yaw。
- shell：运行 shell 命令。
- signing：签名控制。
- status：显示状态。
- switch：飞行模式开关控制。
- takeoff：起飞。
- terrain：地形控制。
- time：显示自动驾驶仪时间。
- tuneopt：选择 Tune Pot 上的选项（仅限四轴飞行器）。
- up：最大调整俯仰修正角度为5度。
- vehicle：车辆控制。
- velocity：速度信息。
- version：获取自动驾驶仪版本。
- watch：监视 MAVLink 模式。
- wipe_parameters：清除自动驾驶仪参数。