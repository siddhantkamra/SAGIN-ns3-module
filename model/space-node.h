#ifndef SPACE_NODE_H
#define SPACE_NODE_H

#include "sagin-node.h"

namespace ns3 {

class SpaceNode : public SaginNode {
public:
  static TypeId GetTypeId (void);

  SpaceNode (double radius);
  SpaceNode ();
  
  virtual ~SpaceNode ();

  void SetPosition (double angleX, double angleY);
  Vector3D GetPosition (void) const;

private:
  double m_radius;     // Fixed radial distance from Earth’s center
  double m_angleX;     // Angle in X-axis for orbital position
  double m_angleY;     // Angle in Y-axis for orbital position
};

} // namespace ns3

#endif /* SPACE_NODE_H */
