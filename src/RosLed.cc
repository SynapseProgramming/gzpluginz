#include "gzpluginz/RosLedPlugin.h"

namespace gazebo {

void RosLed::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf) {

  LedPlugin::Load(_parent, _sdf);
  std::cout << "YESSSS\n";
  this->TurnOnAll();
  // this->TurnOffAll();
}

} // namespace gazebo
