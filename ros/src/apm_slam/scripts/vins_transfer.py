import rospy
from geometry_msgs.msg import PoseStamped, Point
from nav_msgs.msg import Odometry
import math
from pyquaternion import Quaternion
import tf
import sys

# 从命令行参数中获取车辆类型和车辆ID
vehicle_type = sys.argv[1]
vehicle_id = sys.argv[2]

# 创建一个PoseStamped类型的对象local_pose
local_pose = PoseStamped()
local_pose.header.frame_id = 'world'

# 使用欧拉角创建四元数
quaternion = tf.transformations.quaternion_from_euler(0, -math.pi/2, math.pi/2)
q = Quaternion([quaternion[3], quaternion[0], quaternion[1], quaternion[2]])

# 定义回调函数vins_callback，用于处理接收到的数据
def vins_callback(data):
    # 将接收到的位置和姿态数据复制到local_pose对象中
    local_pose.pose.position.x = data.pose.pose.position.x
    local_pose.pose.position.y = data.pose.pose.position.y
    local_pose.pose.position.z = data.pose.pose.position.z

    # 将接收到的四元数转换为pyquaternion库的Quaternion对象
    q_ = Quaternion([data.pose.pose.orientation.w, data.pose.pose.orientation.x, data.pose.pose.orientation.y, data.pose.pose.orientation.z])

    # 将接收到的姿态数据与预先定义的四元数相乘，实现旋转
    q_ = q_ * q

    # 将旋转后的四元数分量赋值给local_pose对象
    local_pose.pose.orientation.w = q_[0]
    local_pose.pose.orientation.x = q_[1]
    local_pose.pose.orientation.y = q_[2]
    local_pose.pose.orientation.z = q_[3]
    
# 初始化ROS节点
rospy.init_node(vehicle_type+"_"+vehicle_id+'_vins_transfer')

# 订阅"/vins_estimator/camera_pose"主题，回调函数为vins_callback
rospy.Subscriber("/vins_estimator/camera_pose", Odometry, vins_callback, queue_size=1)

# 创建一个Publisher，用于发布local_pose对象到"vehicle_type_vehicle_id/mavros/vision_pose/pose"主题
position_pub = rospy.Publisher(vehicle_type+"_"+vehicle_id+"/mavros/vision_pose/pose", PoseStamped, queue_size=1)

# 设置循环的频率为30Hz
rate = rospy.Rate(30)

# 循环直到节点被关闭
while not rospy.is_shutdown():
    # 检查local_pose是否已经接收到位置信息，如果没有，则继续循环
    if (local_pose.pose.position == Point()):
        continue
    else:
        # 如果接收到了位置信息，则打印消息并设置时间戳，然后发布local_pose对象
        print("Vins pose received")
        local_pose.header.stamp = rospy.Time.now()
        position_pub.publish(local_pose)

    try:
        rate.sleep()
    except:
        continue

