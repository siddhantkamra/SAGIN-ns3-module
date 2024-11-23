#include "aerial-node.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("AerialNode");
NS_OBJECT_ENSURE_REGISTERED(AerialNode);

TypeId
AerialNode::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::AerialNode")
                            .SetParent<SaginNode>()
                            .SetGroupName("SAGIN")
                            .AddConstructor<AerialNode>();
    return tid;
}

// Default constructor
AerialNode::AerialNode()
    : SaginNode(0, NodeType::AERIAL_NODE),  // Default uniqueId set to 0
      m_type(UAV), m_uavAltitude(0), m_coverageRadius(0), m_bandwidth(0), m_energyConstraints(0), m_mobilityPattern(""),
      m_interferenceLevel(0), m_collisionAvoidance(false), m_latencyRequirement(0)
{
    // Default mobility model setup based on aerial node type
    m_mobility = CreateObject<ConstantPositionMobilityModel>();  // Default to position model
}

// Constructor with specific AerialType
AerialNode::AerialNode(AerialType type)
    : SaginNode(0, NodeType::AERIAL_NODE),
      m_type(type), m_interferenceLevel(0), m_collisionAvoidance(false), m_latencyRequirement(0)
{
    if (m_type == UAV || m_type == HAPS) {
        m_mobility = CreateObject<ConstantVelocityMobilityModel>();
    } else {
        m_mobility = CreateObject<ConstantPositionMobilityModel>();
    }
}

// Constructor with specific AerialType and uniqueId
AerialNode::AerialNode(AerialType type, int uniqueId)
    : SaginNode(uniqueId, NodeType::AERIAL_NODE),
      m_type(type), m_interferenceLevel(0), m_collisionAvoidance(false), m_latencyRequirement(0)
{
    if (m_type == UAV || m_type == HAPS) {
        m_mobility = CreateObject<ConstantVelocityMobilityModel>();
    } else {
        m_mobility = CreateObject<ConstantPositionMobilityModel>();
    }
}

// Destructor
AerialNode::~AerialNode() {}

void
AerialNode::SetPosition(const Vector& position)
{
    m_mobility->SetPosition(position);
    NS_LOG_INFO("Position set to " << m_mobility->GetPosition());
}

Vector
AerialNode::GetPosition(void) const
{
    return m_mobility->GetPosition();
}

void
AerialNode::SetVelocity(const Vector& velocity)
{
    Ptr<ConstantVelocityMobilityModel> velocityModel = m_mobility->GetObject<ConstantVelocityMobilityModel>();
    if (velocityModel != nullptr) {
        velocityModel->SetVelocity(velocity);
        NS_LOG_INFO("Velocity set to " << velocity);
    } else {
        NS_LOG_WARN("Velocity model not available for this aerial node type.");
    }
}

Vector
AerialNode::GetVelocity(void) const
{
    Ptr<ConstantVelocityMobilityModel> velocityModel = m_mobility->GetObject<ConstantVelocityMobilityModel>();
    if (velocityModel != nullptr) {
        return velocityModel->GetVelocity();
    }
    return Vector(0.0, 0.0, 0.0);  // Return zero if no velocity model
}

// Start mobility updates periodically
void
AerialNode::StartMobilityUpdate(double interval)
{
    Simulator::Schedule(Seconds(interval), &AerialNode::UpdatePosition, this, interval);
}

// Update position based on velocity and time interval
void
AerialNode::UpdatePosition(double interval)
{
    Ptr<ConstantVelocityMobilityModel> velocityModel = m_mobility->GetObject<ConstantVelocityMobilityModel>();
    if (velocityModel != nullptr) {
        Vector currentPos = velocityModel->GetPosition();
        Vector velocity = velocityModel->GetVelocity();
        Vector newPos(currentPos.x + velocity.x * interval,
                      currentPos.y + velocity.y * interval,
                      currentPos.z + velocity.z * interval);
        velocityModel->SetPosition(newPos);
        NS_LOG_INFO("Updated position to " << newPos);
    }
    // Schedule the next update
    Simulator::Schedule(Seconds(interval), &AerialNode::UpdatePosition, this, interval);
}

void AerialNode::SetUavAltitude(double altitude) {
    m_uavAltitude = altitude;
}

double AerialNode::GetUavAltitude(void) const {
    return m_uavAltitude;
}

void AerialNode::SetCoverageRadius(double radius) {
    m_coverageRadius = radius;
}

double AerialNode::GetCoverageRadius(void) const {
    return m_coverageRadius;
}

void AerialNode::SetBandwidth(double bandwidth) {
    m_bandwidth = bandwidth;
}

double AerialNode::GetBandwidth(void) const {
    return m_bandwidth;
}

void AerialNode::SetEnergyConstraints(double energy) {
    m_energyConstraints = energy;
}

double AerialNode::GetEnergyConstraints(void) const {
    return m_energyConstraints;
}

void AerialNode::SetMobilityPattern(const std::string& pattern) {
    m_mobilityPattern = pattern;
}

std::string AerialNode::GetMobilityPattern(void) const {
    return m_mobilityPattern;
}

void AerialNode::SetInterferenceLevel(double interference) {
    m_interferenceLevel = interference;
}

double AerialNode::GetInterferenceLevel(void) const {
    return m_interferenceLevel;
}

void AerialNode::SetCollisionAvoidance(bool enable) {
    m_collisionAvoidance = enable;
}

bool AerialNode::GetCollisionAvoidance(void) const {
    return m_collisionAvoidance;
}

void AerialNode::SetLatencyRequirement(double latency) {
    m_latencyRequirement = latency;
}

double AerialNode::GetLatencyRequirement(void) const {
    return m_latencyRequirement;
}

}  // namespace ns3
