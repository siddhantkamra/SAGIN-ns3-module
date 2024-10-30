// ground-node.cc
#include "ground-node.h"
#include "ns3/log.h"
#include "ns3/socket.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/inet-socket-address.h"
#include "ns3/simulator.h"
#include "ns3/internet-module.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("GroundNode");
NS_OBJECT_ENSURE_REGISTERED (GroundNode);

TypeId
GroundNode::GetTypeId (void) {
  static TypeId tid = TypeId ("ns3::GroundNode")
    .SetParent<SaginNode> ()
    .SetGroupName ("SAGIN")
    .AddConstructor<GroundNode> ();
  return tid;
}

GroundNode::GroundNode ()
  : m_socket (0) {}

GroundNode::~GroundNode () {
  m_socket = 0;
}

void GroundNode::SetPosition (const Vector2D &position) {
  m_position = position;
}

Vector2D GroundNode::GetPosition (void) const {
  return m_position;
}

// void GroundNode::SetupSocket (Address address, uint16_t port) {
//   if (m_socket == nullptr) {
//     m_socket = Socket::CreateSocket (GetNode (), UdpSocketFactory::GetTypeId ());
//     m_socket->Bind (InetSocketAddress (Ipv4Address::GetAny (), port));
//     m_socket->SetRecvCallback (MakeCallback (&GroundNode::ReceivePacket, this));
//     NS_LOG_INFO ("Socket setup complete for GroundNode with address: " << address << " on port: " << port);
//   }
// }

void GroundNode::SetupSocket (Address address, uint16_t port) {
  if (m_socket == nullptr) {
    // Use the GetNode() method to get the node pointer
    Ptr<Node> node = GetNode ();
    if (node != nullptr) {
      m_socket = Socket::CreateSocket (node, UdpSocketFactory::GetTypeId ());
      m_socket->Bind (InetSocketAddress (Ipv4Address::GetAny (), port));
      m_socket->SetRecvCallback (MakeCallback (&GroundNode::ReceivePacket, this));
      NS_LOG_INFO ("Socket setup complete for GroundNode with address: " << address << " on port: " << port);
    } else {
      NS_LOG_ERROR ("Node pointer is null in GroundNode");
    }
  }
}

void GroundNode::SendPacket (Ptr<Packet> packet, Address destinationAddress, uint16_t port) {
  if (m_socket) {
    m_socket->Connect (InetSocketAddress (Ipv4Address::ConvertFrom (destinationAddress), port));
    m_socket->Send (packet);
    NS_LOG_INFO ("GroundNode sent packet to " << InetSocketAddress::ConvertFrom (destinationAddress).GetIpv4 () << ":" << port);
  } else {
    NS_LOG_ERROR ("Socket not initialized in GroundNode");
  }
}

void GroundNode::ReceivePacket (Ptr<Socket> socket) {
  Ptr<Packet> packet = socket->Recv ();
  NS_LOG_INFO ("GroundNode received packet of size: " << packet->GetSize ());
  ProcessData (packet);  // Process the received data
}

void GroundNode::ProcessData (Ptr<Packet> packet) {
  NS_LOG_INFO ("GroundNode processing data of packet size: " << packet->GetSize ());
  // Implement custom data processing here (parsing packet content, responding, etc.)
}

} // namespace ns3