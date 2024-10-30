// space-node.cc
#include "space-node.h"
#include "ns3/log.h"
#include <cmath>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("SpaceNode");

NS_OBJECT_ENSURE_REGISTERED (SpaceNode);

TypeId
SpaceNode::GetTypeId (void) {
  static TypeId tid = TypeId ("ns3::SpaceNode")
    .SetParent<SaginNode> ()
    .SetGroupName ("SAGIN")
    .AddConstructor<SpaceNode> ();
  return tid;
}

SpaceNode::SpaceNode (double radius) : m_radius(radius), m_angleX(0), m_angleY(0) {}

SpaceNode::SpaceNode() 
    : m_radius(1.0), m_angleX(0), m_angleY(0) { // Default constructor with initial values
}

SpaceNode::~SpaceNode () {}

void SpaceNode::SetPosition (double angleX, double angleY) {
  m_angleX = angleX;
  m_angleY = angleY;
  // Compute 3D coordinates based on spherical to Cartesian conversion
}

Vector3D SpaceNode::GetPosition (void) const {
  // Convert spherical coordinates to Cartesian
  double x = m_radius * std::cos(m_angleX) * std::cos(m_angleY);
  double y = m_radius * std::cos(m_angleX) * std::sin(m_angleY);
  double z = m_radius * std::sin(m_angleX);
  return Vector3D (x, y, z);
}

} // namespace ns3
