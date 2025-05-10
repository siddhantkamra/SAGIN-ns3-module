#ifndef GROUND_NODE_H
#define GROUND_NODE_H

#include "sagin-node.h"
#include "ns3/vector.h"
#include "ns3/mobility-model.h"

namespace ns3
{

class GroundNode : public SaginNode
{
public:
    static TypeId GetTypeId(void);

    GroundNode();
    GroundNode(int uniqueId);
    ~GroundNode();

    void SetPosition(const Vector& position);
    Vector GetPosition(void) const;

    void SetVelocity(const Vector& velocity);
    Vector GetVelocity(void) const;

    void StartPositionUpdates(double interval);

    void SetBaseStationDensity(double density);
    double GetBaseStationDensity(void) const;

    void SetNetworkArchitecture(const std::string& architecture);
    std::string GetNetworkArchitecture(void) const;

    void SetUserDensity(double density);
    double GetUserDensity(void) const;

    void SetAccessTechnology(const std::string& technology);
    std::string GetAccessTechnology(void) const;

    void SetLatencyRequirement(double latency);
    double GetLatencyRequirement(void) const;

    void SetEdgeComputingResources(double cpu, double memory);
    std::pair<double, double> GetEdgeComputingResources(void) const;

    void SetHandoffMechanism(const std::string& mechanism);
    std::string GetHandoffMechanism(void) const;

    void SetHandoverLatency(double latency);
    double GetHandoverLatency(void) const;

    void SetCrossLayerBandwidth(double bandwidth);
    double GetCrossLayerBandwidth(void) const;

    void SetCrossLayerLatency(double latency);
    double GetCrossLayerLatency(void) const;

    void SetReliability(double reliability);
    double GetReliability(void) const;

    void SetQoSRequirements(const std::string& qos);
    std::string GetQoSRequirements(void) const;

    void SetSecurityProtocols(const std::string& protocols);
    std::string GetSecurityProtocols(void) const;

private:
    Vector m_position;               // 3D position: (x, y, z) as Vector
    Vector m_velocity;               // Velocity vector
    Ptr<MobilityModel> m_mobility;   // Mobility model for dynamic movement
    EventId m_updateEvent;           // Event to periodically update position
    double m_updateInterval;         // Interval for position updates

    void UpdatePosition();           // Method to periodically update position

    double m_baseStationDensity;
    std::string m_networkArchitecture;
    double m_userDensity;
    std::string m_accessTechnology;
    double m_latencyRequirement;
    double m_edgeCpu;
    double m_edgeMemory;
    std::string m_handoffMechanism;

    double m_handoverLatency;
    double m_crossLayerBandwidth;
    double m_crossLayerLatency;
    double m_reliability;
    std::string m_qosRequirements;
    std::string m_securityProtocols;
};

} // namespace ns3

#endif // GROUND_NODE_H
