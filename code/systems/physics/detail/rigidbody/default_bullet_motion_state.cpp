#include <systems/physics/detail/rigidbody/default_bullet_motion_state.hpp>
#include <systems/transform/transform_controller.hpp>
#include <systems/physics/detail/rigidbody/bullet_to_gl_tranform.hpp>


namespace Bullet {
namespace Detail {


Default_motion_state::Default_motion_state(const Core::Entity e, const Core::World w)
: m_entity(e)
, m_world(w)
{
  
}


void
Default_motion_state::getWorldTransform(btTransform &world_trans) const
{
  math::transform trans;
  Transform::get(m_world, m_entity, trans);
  
  world_trans = gl_to_bullget(trans);
}


void
Default_motion_state::setWorldTransform(const btTransform &world_trans)
{
  Transform::set(m_world, m_entity, bullet_to_gl(world_trans));
}


} // ns
} // ns