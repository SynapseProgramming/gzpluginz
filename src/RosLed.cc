#include "gzpluginz/RosLedPlugin.h"

namespace gazebo {

void RosLed::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf) {

  // Make sure the ROS node for Gazebo has already been initialized
  if (!ros::isInitialized()) {
    ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable "
                     "to load plugin. "
                     << "Load the Gazebo system plugin "
                        "'libgazebo_ros_api_plugin.so' in the gazebo_ros "
                        "package)");
    return;
  }
  ROS_INFO("RosLed Gazebo ROS plugin loading.");

  LedPlugin::Load(_parent, _sdf);
  std::cout << "YESSSS\n";

  // ROS service to receive a command to control the light
  ros::NodeHandle n;
  this->service = n.advertiseService("lights", &RosLed::Control, this);
}

bool RosLed::Control(std_srvs::SetBool::Request &_req,
                     std_srvs::SetBool::Response &_res) {
  if (_req.data) {
    _res.success = this->TurnOnAll();
  } else {
    _res.success = this->TurnOffAll();
  }

  return _res.success;
}

} // namespace gazebo
