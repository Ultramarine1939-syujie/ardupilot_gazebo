# ROS使用参考

#### 二维雷达的使用

```xml
        <plugin name="hokuyo_node" filename="libgazebo_ros_laser.so">
          <robotNamespace></robotNamespace>
          <topicName>/spur/laser/scan</topicName>
          <frameName>/hokuyo_sensor_link</frameName>
        </plugin>
```

Fixed Frame choose the "hokuyo_sensor_link" to show laser data

在上述的配置中，"frameName"指定了激光传感器的坐标系名称为"/hokuyo_sensor_link"。这意味着激光传感器的扫描数据将以这个坐标系作为参考坐标系进行发布。这样，其他节点或算法可以使用这个坐标系来正确地解释激光数据，并将其与其他传感器数据进行融合。