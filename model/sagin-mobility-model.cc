#include "sagin-mobility-model.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("SaginMobilityModel");
NS_OBJECT_ENSURE_REGISTERED(SaginMobilityModel);

TypeId SaginMobilityModel::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::SaginMobilityModel")
        .SetParent<MobilityModel>()
        .SetGroupName("Mobility")
        .AddConstructor<SaginMobilityModel>();
    return tid;
}

SaginMobilityModel::SaginMobilityModel()
    : m_position(Vector(0.0, 0.0, 0.0)),
      m_velocity(Vector(0.0, 0.0, 0.0)),
      m_nodeType(GROUND) // Default to ground node
{
}

void SaginMobilityModel::SetNodeType(NodeType type)
{
    m_nodeType = type;
}

void SaginMobilityModel::SetInitialPosition(const Vector &position)
{
    m_position = position;
}

void SaginMobilityModel::SetAerialMobilityModel(const std::string &modelType)
{
    if (m_nodeType == AERIAL)
    {
        m_aerialMobilityType = modelType;
    }
}

Vector SaginMobilityModel::DoGetPosition(void) const
{
    //UpdatePosition(Simulator::Now().GetSeconds());
    return m_position;
}

void SaginMobilityModel::DoSetPosition(const Vector &position)
{
    m_position = position;
}

Vector SaginMobilityModel::DoGetVelocity(void) const
{
    return m_velocity;
}

void SaginMobilityModel::UpdatePosition(double timeStep)
{
    if (m_nodeType == GROUND)
    {
        // Ground nodes are fixed, no position update needed
        return;
    }
    else if (m_nodeType == AERIAL)
    {
        // Example aerial mobility logic (simple circular or linear movement)
        if (m_aerialMobilityType == "UAV")
        {
            m_position.x += m_velocity.x * timeStep;
            m_position.y += m_velocity.y * timeStep;
            m_position.z += m_velocity.z * timeStep;
        }
        else if (m_aerialMobilityType == "Balloon")
        {
            // Balloon has vertical movement only as an example
            m_position.z += m_velocity.z * timeStep;
        }
        // Add additional aerial models if needed
    }
    else if (m_nodeType == SPACE)
    {
        // Simplified orbital movement (satellite with constant radius from Earth center)
        double radius = m_position.GetLength(); // Assume fixed distance
        double angle = Simulator::Now().GetSeconds() * 0.001; // Example angular speed
        m_position.x = radius * cos(angle);
        m_position.y = radius * sin(angle);
    }
}

} // namespace ns3
