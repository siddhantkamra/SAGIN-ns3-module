#include "sagin-helper.h"
#include "ground-node.h"
#include "aerial-node.h"
#include "space-node.h"
#include "ns3/vector.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("SaginHelper");

SaginHelper::SaginHelper() {
  // Constructor implementation
}

SaginHelper::~SaginHelper() {
  // Destructor implementation
}

Ptr<GroundNode> SaginHelper::CreateGroundNode(const Vector &position) {
  Ptr<GroundNode> groundNode = CreateObject<GroundNode>();
  groundNode->SetPosition(Vector2D(position.x, position.y));  // Adjust for 2D
  m_groundNodes.Add(groundNode);
  return groundNode;
}

Ptr<AerialNode> SaginHelper::CreateAerialNode(const Vector &position, AerialType type) {
  Ptr<AerialNode> aerialNode = CreateObject<AerialNode>(type);
  aerialNode->SetPosition(Vector3D(position.x, position.y, position.z));  // Adjust for 3D
  m_aerialNodes.Add(aerialNode);
  return aerialNode;
}

Ptr<SpaceNode> SaginHelper::CreateSpaceNode(const Vector &position) {
  Ptr<SpaceNode> spaceNode = CreateObject<SpaceNode>();
  spaceNode->SetPosition(position.x, position.y);  // Using spherical coordinates
  m_spaceNodes.Add(spaceNode);
  return spaceNode;
}

}  // namespace ns3

