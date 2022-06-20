#include "gzpluginz/RosElevatorPlugin.h"

namespace gazebo {

void RosElevator::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf) {

  gazebo_ros_ = GazeboRosPtr(new GazeboRos(_parent, _sdf, "LiftControl"));
  // Make sure the ROS node for Gazebo has already been initialized
  gazebo_ros_->isInitialized();
  ROS_INFO("RosElevator Gazebo ROS plugin loading.");

  // ElevatorPlugin::Load(_parent, _sdf);
  // door_joint =
  //     gazebo_ros_->getJoint(parent, "steeringJoint", "front_steering_joint");
  // ROS service to receive a command to control the light
  this->service = gazebo_ros_->node()->advertiseService(
      "floor", &RosElevator::Control, this);
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
