#include <systems/physics/detail/rigidbody/default_bullet_motion_state.hpp>


namespace Bullet {
namespace Detail {


Default_motion_state::Default_motion_state()
{
}


void
Default_motion_state::getWorldTransform(btTransform &world_trans) const
{
  // Get world transform.
}


void
Default_motion_state::setWorldTransform(const btTransform &world_trans)
{
  // Set transform.
}


} // ns
} // ns