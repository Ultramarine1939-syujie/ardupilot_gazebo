# Mavros使用参考

#### IMU频率提高

mavros中的IMU话题有两个，一个原始数据，另外一个是飞控计算过后的IMU数据。下面介绍几种方法来提高两个IMU话题的发布频率。

使用前提：需要提高对应数据接口的波特率以应对增大的数据量。

1.在 QGC Mavlink 控制台中执行以下命令：

```
mavlink stream -d /dev/ttyS1 -s HIGHRES_IMU -r 100
mavlink stream -d /dev/ttyS1 -s ATTITUDE_QUATERNION -r 100
```

2.在终端中(26对应data_raw、31对应data)

```
rosrun mavros mavcmd long 511 26 10000 0 0 0 0 0		#data_raw
rosrun mavros mavcmd long 511 31 10000 0 0 0 0 0		#data
```

3、直接修改参数：https://ardupilot.org/dev/docs/mavlink-requesting-data.html