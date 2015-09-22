#ifndef ACTOR_MOTION_STATE_INCLUDED_0EACC6BF_A263_44BF_8FDE_64536AC6F740
#define ACTOR_MOTION_STATE_INCLUDED_0EACC6BF_A263_44BF_8FDE_64536AC6F740


#include <bullet/btBulletDynamicsCommon.h>
#include <core/entity/entity.hpp>
#include <core/world/world.hpp>
#include <math/quat/quat.hpp>


namespace Bullet {
namespace Detail {


/*
  Actor motion state
  --
*/
class Actor_motion_state : public btMotionState
{
public:

  explicit      Actor_motion_state(const Core::World w, const Core::Entity e);
  
  void          getWorldTransform(btTransform& world_trans) const override;
  void          setWorldTransform(const btTransform& world_trans) override;
  
private:

  const Core::World   m_world;
  const Core::Entity  m_entity;
  math::quat          m_head_rotation_offset;
  
}; // class


} // ns
} // ns


#endif // inc guard