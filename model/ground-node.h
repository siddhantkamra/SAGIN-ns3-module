// ground-node.h
#ifndef GROUND_NODE_H
#define GROUND_NODE_H

#include "sagin-node.h"
#include "ns3/vector.h"
#include "ns3/address.h"
#include "ns3/socket.h"

namespace ns3 {

class GroundNode : public SaginNode {
public:
  static TypeId GetTypeId (void);

  GroundNode ();
  ~GroundNode ();

  void SetPosition (const Vector2D &position);
  Vector2D GetPosition (void) const;

  // New methods for socket and communication functionality
  void SetupSocket (Address address, uint16_t port);
  void SendPacket (Ptr<Packet> packet, Address destinationAddress, uint16_t port);
  void ReceivePacket (Ptr<Socket> socket);
  void ProcessData (Ptr<Packet> packet);

private:
  Vector2D m_position;
  Ptr<Socket> m_socket; // Socket for packet communication
};

} // namespace ns3

#endif // GROUND_NODE_H