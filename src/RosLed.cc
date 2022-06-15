#include "gzpluginz/RosLedPlugin.h"

namespace gazebo {

void RosLed::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf) {

  LedPlugin::Load(_parent, _sdf);
  this->TurnOnAll();
}

} // namespace gazebo
