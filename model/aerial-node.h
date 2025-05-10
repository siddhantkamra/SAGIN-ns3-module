#ifndef AERIAL_NODE_H
#define AERIAL_NODE_H

#include "sagin-node.h"
#include "ns3/mobility-model.h"
#include "ns3/vector.h"
#include "ns3/constant-velocity-mobility-model.h"
#include "ns3/constant-position-mobility-model.h"

namespace ns3 {

// Enum for different types of aerial nodes
enum AerialType
{
    UAV,
    BALLOON,
    HAPS
};

class AerialNode : public SaginNode
{
public:
    static TypeId GetTypeId(void);

    AerialNode();
    AerialNode(AerialType type);
    AerialNode(AerialType type, int uniqueId);
    ~AerialNode();

    // Set and Get methods for Position and Velocity
    void SetPosition(const Vector& position);
    Vector GetPosition(void) const;

    void SetVelocity(const Vector& velocity);
    Vector GetVelocity(void) const;

    // Method to start updating mobility periodically
    void StartMobilityUpdate(double interval);

    void SetUavAltitude(double altitude);
    double GetUavAltitude(void) const;

    void SetCoverageRadius(double radius);
    double GetCoverageRadius(void) const;

    void SetBandwidth(double bandwidth);
    double GetBandwidth(void) const;

    void SetEnergyConstraints(double energy);
    double GetEnergyConstraints(void) const;

    void SetMobilityPattern(const std::string& pattern);
    std::string GetMobilityPattern(void) const;

    void SetInterferenceLevel(double interference);
    double GetInterferenceLevel(void) const;

    void SetCollisionAvoidance(bool enable);
    bool GetCollisionAvoidance(void) const;

    void SetLatencyRequirement(double latency);
    double GetLatencyRequirement(void) const;

private:
    AerialType m_type;   // Type of aerial node (e.g., UAV, HAPS)
    Ptr<MobilityModel> m_mobility;  // Pointer to mobility model

    double m_uavAltitude;
    double m_coverageRadius;
    double m_bandwidth;
    double m_energyConstraints;
    std::string m_mobilityPattern;

    double m_interferenceLevel;
    bool m_collisionAvoidance;
    double m_latencyRequirement;

    // Method to update position based on velocity and time interval
    void UpdatePosition(double interval);
};

} // namespace ns3

#endif /* AERIAL_NODE_H */
