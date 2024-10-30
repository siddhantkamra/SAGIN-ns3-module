#ifndef SAGIN_MOBILITY_MODEL_H
#define SAGIN_MOBILITY_MODEL_H

#include "ns3/mobility-model.h"
#include "ns3/vector.h"

namespace ns3 {

enum NodeType
{
    GROUND,
    AERIAL,
    SPACE
};

class SaginMobilityModel : public MobilityModel {
public:
  static TypeId GetTypeId (void);

  SaginMobilityModel ();
  //virtual ~SaginMobilityModel ();

  void SetNodeType(NodeType type);

  void SetInitialPosition (const Vector& position);
  void SetVelocity (const Vector& velocity);

  // Functions to configure Aerial Node mobility type (e.g., UAV, Balloon)
  void SetAerialMobilityModel(const std::string &modelType);

protected:
  virtual Vector DoGetPosition(void) const override;
  virtual void DoSetPosition(const Vector &position) override;
  virtual Vector DoGetVelocity(void) const override;

private:
  Vector m_position;
  Vector m_velocity;
  NodeType m_nodeType;
  std::string m_aerialMobilityType;

  void UpdatePosition(double timeStep);
};

} // namespace ns3

#endif /* SAGIN_MOBILITY_MODEL_H */
