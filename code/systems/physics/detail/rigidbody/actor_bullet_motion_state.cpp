#include <systems/physics/detail/rigidbody/actor_bullet_motion_state.hpp>
#include <systems/transform/transform_controller.hpp>
#include <systems/physics/detail/rigidbody/bullet_to_gl_tranform.hpp>


namespace Bullet {
namespace Detail {


Actor_motion_state::Actor_motion_state(const Core::World w, const Core::Entity e)
: m_world(w)
, m_entity(e)
{
}


void
Actor_motion_state::getWorldTransform(btTransform &world_trans) const
{
  math::transform trans;
  Transform::get(m_world, m_entity, trans);
  
  world_trans = gl_to_bullet(trans);
}


void
Actor_motion_state::setWorldTransform(const btTransform &world_trans)
{
  Transform::set(m_world, m_entity, bullet_to_gl(world_trans));
}


} // ns
} // ns