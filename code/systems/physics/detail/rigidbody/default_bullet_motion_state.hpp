#ifndef DEFAULT_BULLET_MOTION_STATE_INCLUDED_868E5F0F_F643_489B_9CA1_621483B5733E
#define DEFAULT_BULLET_MOTION_STATE_INCLUDED_868E5F0F_F643_489B_9CA1_621483B5733E


#include <bullet/btBulletDynamicsCommon.h>


namespace Bullet {
namespace Detail {


class Default_motion_state : public btMotionState
{
public:

  explicit      Default_motion_state();
  
  void          getWorldTransform(btTransform& world_trans) const = 0;
  void          setWorldTransform(const btTransform& world_trans) = 0;

}; // class


} // ns
} // ns


#endif // inc guard