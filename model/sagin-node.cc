#include "sagin-node.h"
#include "ns3/log.h"
#include "ns3/channel.h"
#include "ns3/vector.h"

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (SaginNode);

TypeId
SaginNode::GetTypeId (void) {
  static TypeId tid = TypeId ("ns3::SaginNode")
    .SetParent<Node> ()
    .SetGroupName ("SAGIN")
    .AddConstructor<SaginNode> ();
  return tid;
}

SaginNode::SaginNode () {}

SaginNode::~SaginNode () {}

void SaginNode::SetPosition (const Vector &position) {
  m_position = position;
}

Vector SaginNode::GetPosition (void) const {
  return m_position;
}

void SaginNode::SetNode (Ptr<Node> node) {
  m_node = node;
}

Ptr<Node> SaginNode::GetNode (void) const {
  return m_node;
}

} // namespace ns3
