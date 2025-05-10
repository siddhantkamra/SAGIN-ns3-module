#include "ground-node.h"
#include "ns3/log.h"
#include "ns3/constant-velocity-mobility-model.h"
#include "ns3/simulator.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("GroundNode");
NS_OBJECT_ENSURE_REGISTERED(GroundNode);

TypeId
GroundNode::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::GroundNode")
                            .SetParent<SaginNode>()
                            .SetGroupName("SAGIN")
                            .AddConstructor<GroundNode>();
    return tid;
}

GroundNode::GroundNode()
    : SaginNode(0, NodeType::GROUND_NODE),
      m_position(Vector(0.0, 0.0, 0.0)),
      m_velocity(Vector(0.0, 0.0, 0.0)),
      m_updateInterval(1.0), // Default update interval in seconds
      m_baseStationDensity(0.0),
      m_networkArchitecture(""),
      m_userDensity(0.0),
      m_accessTechnology(""),
      m_latencyRequirement(0.0),
      m_edgeCpu(0.0),
      m_edgeMemory(0.0),
      m_handoffMechanism(""),
      m_handoverLatency(0), m_crossLayerBandwidth(0), m_crossLayerLatency(0), m_reliability(0), m_qosRequirements(""), m_securityProtocols("")
{
    m_mobility = CreateObject<ConstantVelocityMobilityModel>();
}

GroundNode::GroundNode(int uniqueId)
    : SaginNode(uniqueId, NodeType::GROUND_NODE),
      m_position(Vector(0.0, 0.0, 0.0)),
      m_velocity(Vector(0.0, 0.0, 0.0)),
      m_updateInterval(1.0), // Default update interval in seconds
      m_baseStationDensity(0.0),
      m_networkArchitecture(""),
      m_userDensity(0.0),
      m_accessTechnology(""),
      m_latencyRequirement(0.0),
      m_edgeCpu(0.0),
      m_edgeMemory(0.0),
      m_handoffMechanism(""),
      m_handoverLatency(0), m_crossLayerBandwidth(0), m_crossLayerLatency(0), m_reliability(0), m_qosRequirements(""), m_securityProtocols("")
{
    m_mobility = CreateObject<ConstantVelocityMobilityModel>();
}

GroundNode::~GroundNode()
{
    if (m_updateEvent.IsPending())
    {
        Simulator::Cancel(m_updateEvent);
    }
}

void
GroundNode::SetPosition(const Vector& position)
{
    m_position = position;
    m_mobility->SetPosition(position);
}

Vector
GroundNode::GetPosition(void) const
{
    return m_mobility->GetPosition();
}

void
GroundNode::SetVelocity(const Vector& velocity)
{
    m_velocity = velocity;
    if (m_mobility->GetObject<ConstantVelocityMobilityModel>())
    {
        m_mobility->GetObject<ConstantVelocityMobilityModel>()->SetVelocity(velocity);
    }
}

Vector
GroundNode::GetVelocity(void) const
{
    return m_velocity;
}

void
GroundNode::StartPositionUpdates(double interval)
{
    m_updateInterval = interval;
    m_updateEvent = Simulator::Schedule(Seconds(interval), &GroundNode::UpdatePosition, this);
}

void
GroundNode::UpdatePosition()
{
    m_position.x += m_velocity.x * m_updateInterval;
    m_position.y += m_velocity.y * m_updateInterval;
    m_position.z += m_velocity.z * m_updateInterval;

    m_mobility->SetPosition(m_position);

    // Log position update
    NS_LOG_INFO("Updated position of GroundNode " << GetId() << " to " << m_position);

    // Reschedule the next update
    m_updateEvent = Simulator::Schedule(Seconds(m_updateInterval), &GroundNode::UpdatePosition, this);
}

void GroundNode::SetBaseStationDensity(double density)
{
    m_baseStationDensity = density;
}

double GroundNode::GetBaseStationDensity(void) const
{
    return m_baseStationDensity;
}

void GroundNode::SetNetworkArchitecture(const std::string& architecture)
{
    m_networkArchitecture = architecture;
}

std::string GroundNode::GetNetworkArchitecture(void) const
{
    return m_networkArchitecture;
}

void GroundNode::SetUserDensity(double density)
{
    m_userDensity = density;
}

double GroundNode::GetUserDensity(void) const
{
    return m_userDensity;
}

void GroundNode::SetAccessTechnology(const std::string& technology)
{
    m_accessTechnology = technology;
}

std::string GroundNode::GetAccessTechnology(void) const
{
    return m_accessTechnology;
}

void GroundNode::SetLatencyRequirement(double latency)
{
    m_latencyRequirement = latency;
}

double GroundNode::GetLatencyRequirement(void) const
{
    return m_latencyRequirement;
}

void GroundNode::SetEdgeComputingResources(double cpu, double memory)
{
    m_edgeCpu = cpu;
    m_edgeMemory = memory;
}

std::pair<double, double> GroundNode::GetEdgeComputingResources(void) const
{
    return std::make_pair(m_edgeCpu, m_edgeMemory);
}

void GroundNode::SetHandoffMechanism(const std::string& mechanism)
{
    m_handoffMechanism = mechanism;
}

std::string GroundNode::GetHandoffMechanism(void) const
{
    return m_handoffMechanism;
}

void GroundNode::SetHandoverLatency(double latency) {
    m_handoverLatency = latency;
}

double GroundNode::GetHandoverLatency(void) const {
    return m_handoverLatency;
}

void GroundNode::SetCrossLayerBandwidth(double bandwidth) {
    m_crossLayerBandwidth = bandwidth;
}

double GroundNode::GetCrossLayerBandwidth(void) const {
    return m_crossLayerBandwidth;
}

void GroundNode::SetCrossLayerLatency(double latency) {
    m_crossLayerLatency = latency;
}

double GroundNode::GetCrossLayerLatency(void) const {
    return m_crossLayerLatency;
}

void GroundNode::SetReliability(double reliability) {
    m_reliability = reliability;
}

double GroundNode::GetReliability(void) const {
    return m_reliability;
}

void GroundNode::SetQoSRequirements(const std::string& qos) {
    m_qosRequirements = qos;
}

std::string GroundNode::GetQoSRequirements(void) const {
    return m_qosRequirements;
}

void GroundNode::SetSecurityProtocols(const std::string& protocols) {
    m_securityProtocols = protocols;
}

std::string GroundNode::GetSecurityProtocols(void) const {
    return m_securityProtocols;
}

} // namespace ns3
