#include <gazebo/common/common.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/plugins/ElevatorPlugin.hh>
#include <gazebo_plugins/gazebo_ros_utils.h>
#include <gzpluginz/lift.h>
#include <iostream>
#include <ros/ros.h>
#include <std_srvs/SetBool.h>

namespace gazebo {

class RosElevator : public ElevatorPlugin {

public:
  void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf) override;

  void Update();

  bool Control(gzpluginz::lift::Request &_req, gzpluginz::lift::Response &_res);

  /// \brief ROS service server.
private:
  ros::ServiceServer service;
  physics::JointPtr door_joint;
  GazeboRosPtr gazebo_ros_;

  event::ConnectionPtr update_connection_;
};

GZ_REGISTER_MODEL_PLUGIN(RosElevator)
} // namespace gazebo
