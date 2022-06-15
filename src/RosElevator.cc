#include "gzpluginz/RosElevatorPlugin.h"

namespace gazebo {

void RosElevator::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf) {

  // Make sure the ROS node for Gazebo has already been initialized
  if (!ros::isInitialized()) {
    ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable "
                     "to load plugin. "
                     << "Load the Gazebo system plugin "
                        "'libgazebo_ros_api_plugin.so' in the gazebo_ros "
                        "package)");
    return;
  }
  ROS_INFO("RosElevator Gazebo ROS plugin loading.");

  ElevatorPlugin::Load(_parent, _sdf);

  // ROS service to receive a command to control the light
  ros::NodeHandle n;
  this->service = n.advertiseService("floor", &RosElevator::Control, this);
}

bool RosElevator::Control(std_srvs::SetBool::Request &_req,
                          std_srvs::SetBool::Response &_res) {
  if (_req.data) {
    this->MoveToFloor(1);
  } else {
    this->MoveToFloor(0);
  }

  return _res.success;
}

} // namespace gazebo
