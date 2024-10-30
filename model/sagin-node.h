#ifndef SAGIN_NODE_H
#define SAGIN_NODE_H

// Add a doxygen group for this module.
// If you have more than one file, this should be in only one of them.
/**
 * \defgroup sagin Description of the sagin
 */



#include "ns3/vector.h"
#include "ns3/node.h"

namespace ns3
{

// Each class should be documented using Doxygen,
// and have an \ingroup sagin directive

class SaginNode : public Node{
public:
  static TypeId GetTypeId (void);

  SaginNode ();
  ~SaginNode ();

  // Set and Get 3D Position
  void SetPosition (const Vector &position);
  Vector GetPosition (void) const;

  void SetNode (Ptr<Node> node);  // Method to set node pointer
  Ptr<Node> GetNode (void) const; // Method to get node pointer

  //set and get ID or communication channel if needed
  //virtual void SetChannel (Ptr<Channel> channel);
  //Ptr<Channel> GetChannel (void) const;

protected:
  Vector m_position; // 3D position of the node
  Ptr<Node> m_node; // Pointer to the node
  //Ptr<Channel> m_channel;
};

}

#endif /* SAGIN_NODE_H */
