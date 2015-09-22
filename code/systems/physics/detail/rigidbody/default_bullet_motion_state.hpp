#ifndef DEFAULT_BULLET_MOTION_STATE_INCLUDED_868E5F0F_F643_489B_9CA1_621483B5733E
#define DEFAULT_BULLET_MOTION_STATE_INCLUDED_868E5F0F_F643_489B_9CA1_621483B5733E


#include <bullet/btBulletDynamicsCommon.h>
#include <core/entity/entity.hpp>
#include <core/world/world.hpp>


namespace Bullet {
namespace Detail {


class Default_motion_state : public btMotionState
{
public:

  explicit      Default_motion_state(const Core::World w, const Core::Entity e);
  
  void          getWorldTransform(btTransform& world_trans) const override;
  void          setWorldTransform(const btTransform& world_trans) override;
  
private:

  const Core::World  m_world;
  const Core::Entity m_entity;

}; // class


} // ns
} // ns


#endif // inc guard