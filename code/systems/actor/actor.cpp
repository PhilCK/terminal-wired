#include <systems/actor/actor.hpp>
#include <math/transform/transform.hpp>
#include <math/vec/vec.hpp>
#include <components/rigid_body/rigid_body_controller.hpp>
#include <utils/logging.hpp>


namespace Actor {


void
turn_right(const Core::Entity e, const float turn)
{
  math::transform actor_trans;
  Component::get(e, actor_trans);

  const math::quat rotation = math::quat_init_with_axis_angle(0, 1, 0, turn);
  const math::quat new_rot  = math::quat_multiply(rotation, actor_trans.rotation);
  
  const math::transform new_transform = math::transform_init(actor_trans.position, actor_trans.scale, new_rot);
  
  Rigidbody::set_transform(e, new_transform);
}


void
move_forward(const Core::Entity e, const float fwd)
{
  Rigidbody::apply_local_force(e, math::vec3_init(0, 0, fwd));
}


void
jump(const Core::Entity e, const float jmp)
{
  util::log_error("Actor::jump not impl");
}


} // ns