#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>

namespace gazebo
{
class PioneerProg : public ModelPlugin
{
  public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
{
  // Store the pointer to the model
  this->model = _parent;

  // Listen to the update event. This event is broadcast every
  // simulation iteration.
  this->updateConnection = event::Events::ConnectWorldUpdateBegin(
      boost::bind(&PioneerProg::OnUpdate, this, _1));
}

// Called by the world update start event
public: void OnUpdate(const common::UpdateInfo & /*_info*/)
{
  // Apply a small linear velocity to the model.
  //this->model->SetLinearVel(math::Vector3(0.06, 0, 0));
joints[LEFT_FRONT_WHEELING] = this->parent->GetJoint(left_wheel_hinge);
joints[LEFT_FRONT_WHEELING]->SetParam("fmax", 0, torque);
joints[LEFT_FRONT_WHEELING]->SetParam("vel", 0, wheel_data_[LEFT_FRONT_WHEELING]/(wheel_diameter_/2.0));

}

// Pointer to the model
private: physics::ModelPtr model;

// Pointer to the update event connection
private: event::ConnectionPtr updateConnection;
};

// Register this plugin with the simulator
GZ_REGISTER_MODEL_PLUGIN(PioneerProg)
}
