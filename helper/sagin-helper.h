#ifndef SAGIN_HELPER_H
#define SAGIN_HELPER_H

//SaginHelper class to simplify adding and configuring nodes in simulation script

#include "ns3/sagin-node.h"
#include "ns3/aerial-node.h"  // Include AerialNode header
#include "ns3/space-node.h"   // Include SpaceNode header
#include "ns3/ground-node.h"  // Include GroundNode header
#include "ns3/node-container.h"
#include "ns3/vector.h"       // Use this for 3D positions

namespace ns3
{

// Each class should be documented using Doxygen,
// and have an \ingroup sagin directive

class SaginHelper {
public:
  SaginHelper(); // Constructor
  ~SaginHelper(); // Destructor

  Ptr<GroundNode> CreateGroundNode(const Vector &position); // Use Vector for 2D position if needed
  Ptr<AerialNode> CreateAerialNode(const Vector &position, AerialType type); // Use Vector for 3D position
  Ptr<SpaceNode> CreateSpaceNode(const Vector &position); // Use Vector for 3D position

private:
  NodeContainer m_groundNodes; // Container for ground nodes
  NodeContainer m_aerialNodes; // Container for aerial nodes
  NodeContainer m_spaceNodes;  // Container for space nodes
};


} // namespace ns3

#endif /* SAGIN_HELPER_H */
