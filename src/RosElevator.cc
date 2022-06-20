#include "gzpluginz/RosElevatorPlugin.h"

namespace gazebo {

void RosElevator::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf) {

  gazebo_ros_ = GazeboRosPtr(new GazeboRos(_parent, _sdf, "LiftControl"));
  // Make sure the ROS node for Gazebo has already been initialized
  gazebo_ros_->isInitialized();
  ROS_INFO("RosElevator Gazebo ROS plugin loading.");

  ElevatorPlugin::Load(_parent, _sdf);
  right_door_joint = gazebo_ros_->getJoint(_parent, "door_joint", "door_joint");
  left_door_joint =
      gazebo_ros_->getJoint(_parent, "left_door_joint", "left_door_joint");
  // ROS service to receive a command to control the light
  this->service = gazebo_ros_->node()->advertiseService(
      "floor", &RosElevator::Control, this);
  // listen to the update event (broadcast every simulation iteration)
  this->update_connection_ = event::Events::ConnectWorldUpdateBegin(
      boost::bind(&RosElevator::Update, this));
}

void RosElevator::Update() {
  double current_angle = right_door_joint->Position(0);

  left_door_joint->SetPosition(0, -current_angle, true);
  std::cout << current_angle << "\n";
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
