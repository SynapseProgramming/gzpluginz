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
  // listen to the update event (broadcast every simulation iteration)
  this->update_connection_ = event::Events::ConnectWorldUpdateBegin(
      boost::bind(&RosElevator::Update, this));
  cnt = 0;
}

void RosElevator::Update() {
  std::cout << cnt << "\n";
  cnt++;
}

bool RosElevator::Control(gzpluginz::lift::Request &_req,
                          gzpluginz::lift::Response &_res) {
  if (_req.floor < 0) {
    _res.status = false;
    return _res.status;
  } else {
    _res.status = true;
    this->MoveToFloor(_req.floor);
    return true;
  }
}

} // namespace gazebo
