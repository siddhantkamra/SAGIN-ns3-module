#include "space-node.h"
#include "ns3/log.h"
#include "ns3/constant-velocity-mobility-model.h"
#include "ns3/simulator.h"
#include <cmath>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("SpaceNode");
NS_OBJECT_ENSURE_REGISTERED(SpaceNode);

TypeId
SpaceNode::GetTypeId(void) {
  static TypeId tid = TypeId("ns3::SpaceNode")
    .SetParent<SaginNode>()
    .SetGroupName("SAGIN")
    .AddConstructor<SpaceNode>();
  return tid;
}

SpaceNode::SpaceNode(double radius, int uniqueId)
    : SaginNode(uniqueId, NodeType::SPACE_NODE),
      m_radius(radius), m_angleX(0), m_angleY(0), m_updateInterval(1.0),
      m_orbitalAltitude(0), m_coverageArea(0), m_bandwidth(0), m_antennaBeamwidth(0), m_propagationDelay(0), m_linkBudget(0),
      m_satelliteType(LEO) // Default to LEO
{
    m_mobility = CreateObject<ConstantVelocityMobilityModel>();
    UpdateMobilityPattern();
}

SpaceNode::SpaceNode() 
    : SaginNode(0, NodeType::SPACE_NODE),
      m_radius(1.0), m_angleX(0), m_angleY(0), m_updateInterval(1.0),
      m_satelliteType(LEO) // Default to LEO
{
    m_mobility = CreateObject<ConstantVelocityMobilityModel>();
    UpdateMobilityPattern();
}

SpaceNode::~SpaceNode() {
    if (m_updateEvent.IsPending()) {
        Simulator::Cancel(m_updateEvent);
    }
}

void SpaceNode::SetPosition(double angleX, double angleY) {
  m_angleX = angleX;
  m_angleY = angleY;

  // Calculate Cartesian coordinates based on spherical coordinates
  double x = m_radius * std::cos(m_angleX) * std::cos(m_angleY);
  double y = m_radius * std::cos(m_angleX) * std::sin(m_angleY);
  double z = m_radius * std::sin(m_angleX);

  Vector3D position(x, y, z);
  m_mobility->SetPosition(position);
}

Vector3D SpaceNode::GetPosition(void) const {
  return m_mobility->GetPosition();
}

void SpaceNode::SetVelocity(const Vector& velocity) {
  m_velocity = velocity;
  if (m_mobility->GetObject<ConstantVelocityMobilityModel>()) {
    m_mobility->GetObject<ConstantVelocityMobilityModel>()->SetVelocity(velocity);
  }
}

Vector SpaceNode::GetVelocity(void) const {
  return m_velocity;
}

void SpaceNode::StartOrbitUpdates(double interval) {
    m_updateInterval = interval;
    m_updateEvent = Simulator::Schedule(Seconds(interval), &SpaceNode::UpdatePosition, this);
}

void SpaceNode::UpdatePosition() {
    // Increment orbital angles based on velocity (simplified orbital dynamics)
    m_angleX += m_velocity.x * m_updateInterval;
    m_angleY += m_velocity.y * m_updateInterval;

    // Calculate new position
    double x = m_radius * std::cos(m_angleX) * std::cos(m_angleY);
    double y = m_radius * std::cos(m_angleX) * std::sin(m_angleY);
    double z = m_radius * std::sin(m_angleX);
    Vector3D position(x, y, z);

    m_mobility->SetPosition(position);

    // Log position update
    NS_LOG_INFO("Updated position of SpaceNode " << GetId() << " to " << position);

    // Reschedule the next update
    m_updateEvent = Simulator::Schedule(Seconds(m_updateInterval), &SpaceNode::UpdatePosition, this);
}

void SpaceNode::SetOrbitalAltitude(double altitude) {
  m_orbitalAltitude = altitude;
}

double SpaceNode::GetOrbitalAltitude(void) const {
  return m_orbitalAltitude;
}

void SpaceNode::SetCoverageArea(double coverageArea) {
  m_coverageArea = coverageArea;
}

double SpaceNode::GetCoverageArea(void) const {
  return m_coverageArea;
}

void SpaceNode::SetBandwidth(double bandwidth) {
  m_bandwidth = bandwidth;
}

double SpaceNode::GetBandwidth(void) const {
  return m_bandwidth;
}

void SpaceNode::SetAntennaBeamwidth(double beamwidth) {
  m_antennaBeamwidth = beamwidth;
}

double SpaceNode::GetAntennaBeamwidth(void) const {
  return m_antennaBeamwidth;
}

void SpaceNode::SetPropagationDelay(double delay) {
  m_propagationDelay = delay;
}

double SpaceNode::GetPropagationDelay(void) const {
  return m_propagationDelay;
}

void SpaceNode::SetLinkBudget(double linkBudget) {
  m_linkBudget = linkBudget;
}

double SpaceNode::GetLinkBudget(void) const {
  return m_linkBudget;
}

void SpaceNode::SetSatelliteType(SatelliteType type) {
  m_satelliteType = type;
  UpdateMobilityPattern();
}

SatelliteType SpaceNode::GetSatelliteType(void) const {
  return m_satelliteType;
}

void SpaceNode::UpdateMobilityPattern() {
  switch (m_satelliteType) {
    case LEO:
      m_orbitalAltitude = 500; // Example altitude for LEO
      m_updateInterval = 1.0; // Example update interval for LEO
      break;
    case MEO:
      m_orbitalAltitude = 20000; // Example altitude for MEO
      m_updateInterval = 10.0; // Example update interval for MEO
      break;
    case GEO:
      m_orbitalAltitude = 35786; // Example altitude for GEO
      m_updateInterval = 0; // GEO satellites are stationary
      break;
  }
}

} // namespace ns3
