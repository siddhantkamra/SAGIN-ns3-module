// aerial-node.h
#ifndef AERIAL_NODE_H
#define AERIAL_NODE_H

#include "sagin-node.h"
#include "ns3/mobility-model.h"

namespace ns3 {

enum AerialType { UAV, BALLOON, HAPS };

class AerialNode : public SaginNode {
public:
  static TypeId GetTypeId (void);

  AerialNode (AerialType type);
  AerialNode ();
  //virtual ~AerialNode ();

  void SetPosition (const Vector3D &position);
  Vector3D GetPosition (void) const;

  void SetVelocity (const Vector &velocity);
  Vector GetVelocity (void) const;

private:
  Vector3D m_position;  // 3D position: (x, y, z)
  Vector m_velocity;
  AerialType m_type;
  Ptr<MobilityModel> m_mobility;  // Mobility model
};

} // namespace ns3

#endif /* AERIAL_NODE_H */
