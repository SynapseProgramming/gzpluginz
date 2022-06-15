#include <gazebo/common/common.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/plugins/LedPlugin.hh>
#include <iostream>
#include <ros/ros.h>
#include <std_srvs/SetBool.h>

namespace gazebo {

class RosLed : public LedPlugin {

public:
  void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf) override;

  bool Control(std_srvs::SetBool::Request &_req,
               std_srvs::SetBool::Response &_res);

  /// \brief ROS service server.
private:
  ros::ServiceServer service;
};

GZ_REGISTER_MODEL_PLUGIN(RosLed)
} // namespace gazebo
