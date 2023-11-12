/*
 * Copyright (C) 2016 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#include <string>
#include <vector>

#include "gazebo/common/PID.hh"
#include "gazebo/physics/physics.hh"
#include "gazebo/transport/transport.hh"
#include "GimbalSmall2dPlugin.hh"

using namespace gazebo;
using namespace std;

GZ_REGISTER_MODEL_PLUGIN(GimbalSmall2dPlugin)

/// \brief Private data class
class gazebo::GimbalSmall2dPluginPrivate  //建立私有变量
{
  /// \brief Callback when a command string is received.
  /// \param[in] _msg Mesage containing the command string
  public: void OnStringMsg(ConstGzStringPtr &_msg);

  /// \brief A list of event connections
  public: std::vector<event::ConnectionPtr> connections;

  /// \brief Subscriber to the gimbal command topic 云台命令主题订阅者
  public: transport::SubscriberPtr sub;

  /// \brief Publisher to the gimbal status topic   云台状态主题的发布者
  public: transport::PublisherPtr pub;

  /// \brief Parent model of this plugin    该插件的父模型
  public: physics::ModelPtr model;  //私有模型变量

  /// \brief Joint for tilting the gimbal   云台倾斜接头
  public: physics::JointPtr tiltJoint;  //私有关节变量

  /// \brief Command that updates the gimbal tilt angle   更新云台倾斜角度的命令
  public: double command = IGN_PI_2;

  /// \brief Pointer to the transport node    指向传输节点的指针
  public: transport::NodePtr node;

  /// \brief PID controller for the gimbal    云台PID控制器
  public: common::PID pid;

  /// \brief Last update sim time   最后更新SIM时间
  public: common::Time lastUpdateTime;
};

/////////////////////////////////////////////////
GimbalSmall2dPlugin::GimbalSmall2dPlugin()
  : dataPtr(new GimbalSmall2dPluginPrivate)
{
  this->dataPtr->pid.Init(1, 0, 0, 0, 0, 1.0, -1.0);
}

/////////////////////////////////////////////////
//利用Load函数加载模型以及sdf文件的标签元素，这些参数是插件作用于模型的桥梁。
//可以把Load方法看作是主函数
void GimbalSmall2dPlugin::Load(physics::ModelPtr _model,  //输入模型变量
  sdf::ElementPtr _sdf) //sdf模型变量
{
  this->dataPtr->model = _model;  //模型赋值

  std::string jointName = "tilt_joint";
  if (_sdf->HasElement("joint"))  
  {
    jointName = _sdf->Get<std::string>("joint");
  }
  this->dataPtr->tiltJoint = this->dataPtr->model->GetJoint(jointName); //关节赋值

  this->dataPtr->PID = common::PID(0.1, 0, 0);

  this->dataPtr->tiltJoint = SetVelocityPID(this->dataPtr->tiltJoint->GetScopedName(), this->pid);

  this->dataPtr->tiltJoint = SetVelocityTarget(this->dataPtr->tiltJoint->GetScopedName(), 10.0);

  if (!this->dataPtr->tiltJoint)
  {
    std::string scopedJointName = _model->GetScopedName() + "::" + jointName; //获取完全限定名称
    gzwarn << "joint [" << jointName
           << "] not found, trying again with scoped joint name ["
           << scopedJointName << "]\n";
    this->dataPtr->tiltJoint = this->dataPtr->model->GetJoint(scopedJointName);
  }
  if (!this->dataPtr->tiltJoint)
  {
    gzerr << "GimbalSmall2dPlugin::Load ERROR! Can't get joint '"
          << jointName << "' " << endl;
  }
}

/////////////////////////////////////////////////
void GimbalSmall2dPlugin::Init()
{
  this->dataPtr->node = transport::NodePtr(new transport::Node());
  this->dataPtr->node->Init(this->dataPtr->model->GetWorld()->GetName());

  this->dataPtr->lastUpdateTime =
    this->dataPtr->model->GetWorld()->GetSimTime();

  std::string topic = std::string("~/") +  this->dataPtr->model->GetName() +
    "/gimbal_tilt_cmd";
  this->dataPtr->sub = this->dataPtr->node->Subscribe(topic,
      &GimbalSmall2dPluginPrivate::OnStringMsg, this->dataPtr.get());

  this->dataPtr->connections.push_back(event::Events::ConnectWorldUpdateBegin(
          std::bind(&GimbalSmall2dPlugin::OnUpdate, this)));

  topic = std::string("~/") +
    this->dataPtr->model->GetName() + "/gimbal_tilt_status";

  this->dataPtr->pub =
    this->dataPtr->node->Advertise<gazebo::msgs::GzString>(topic);
}

/////////////////////////////////////////////////
void GimbalSmall2dPluginPrivate::OnStringMsg(ConstGzStringPtr &_msg)
{
  this->command = atof(_msg->data().c_str());
}

/////////////////////////////////////////////////
void GimbalSmall2dPlugin::OnUpdate()
{
  if (!this->dataPtr->tiltJoint)
    return;

  double angle = this->dataPtr->tiltJoint->GetAngle(0).Radian();

  common::Time time = this->dataPtr->model->GetWorld()->GetSimTime();
  if (time < this->dataPtr->lastUpdateTime)
  {
    this->dataPtr->lastUpdateTime = time;
    return;
  }
  else if (time > this->dataPtr->lastUpdateTime)
  {
    double dt = (this->dataPtr->lastUpdateTime - time).Double();
    double error = angle - this->dataPtr->command;
    double force = this->dataPtr->pid.Update(error, dt);
    this->dataPtr->tiltJoint->SetForce(0, force);
    this->dataPtr->lastUpdateTime = time;
  }

  static int i = 1000;
  if (++i > 100)
  {
    i = 0;
    std::stringstream ss;
    ss << angle;
    gazebo::msgs::GzString m;
    m.set_data(ss.str());
    this->dataPtr->pub->Publish(m);
  }
}
