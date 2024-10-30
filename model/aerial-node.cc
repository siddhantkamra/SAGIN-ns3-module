// aerial-node.cc
#include "aerial-node.h"
#include "ns3/log.h"
#include "ns3/constant-velocity-mobility-model.h"
#include "ns3/constant-position-mobility-model.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("AerialNode");

NS_OBJECT_ENSURE_REGISTERED (AerialNode);

TypeId
AerialNode::GetTypeId (void) {
  static TypeId tid = TypeId ("ns3::AerialNode")
    .SetParent<SaginNode> ()
    .SetGroupName ("SAGIN")
    .AddConstructor<AerialNode> ();
  return tid;
}

// Default constructor
AerialNode::AerialNode() 
    : m_position(Vector3D(0.0, 0.0, 0.0)), 
      m_velocity(Vector(0.0, 0.0, 0.0)), 
      m_type(UAV), 
      m_mobility(CreateObject<ConstantPositionMobilityModel>()) { 
}

AerialNode::AerialNode (AerialType type) : m_type(type) {
  // Set up a different mobility model based on the aerial type
  if (m_type == UAV) {
    m_mobility = CreateObject<ConstantVelocityMobilityModel> ();
  } else if (m_type == BALLOON) {
    m_mobility = CreateObject<ConstantPositionMobilityModel> ();
  } else if (m_type == HAPS) {
    m_mobility = CreateObject<ConstantVelocityMobilityModel> (); // example model
  }
}

// No need for an explicit destructor
// AerialNode::~AerialNode() {}

void AerialNode::SetPosition (const Vector3D &position) {
  m_position = position;
  m_mobility->SetPosition (position);
}

Vector3D AerialNode::GetPosition (void) const {
  //return m_mobility->GetPosition ();
  return m_position; // Return the stored position
}

void AerialNode::SetVelocity (const Vector &velocity) {
  m_velocity = velocity;
  if (m_mobility->GetObject<ConstantVelocityMobilityModel> ()) {
    m_mobility->GetObject<ConstantVelocityMobilityModel> ()->SetVelocity (velocity);
  }
}

Vector AerialNode::GetVelocity (void) const {
  return m_velocity;
}

} // namespace ns3
