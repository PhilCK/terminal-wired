#include <systems/actor/actor.hpp>
#include <systems/transform/transform_controller.hpp>
#include <math/transform/transform.hpp>
#include <math/vec/vec.hpp>
#include <systems/physics/rigidbody_controller.hpp>
#include <utils/logging.hpp>


namespace Actor {


void
turn_right(const Core::Entity e, const float turn)
{
  math::transform actor_trans;
  Transform::get(Core::World{1}, e, actor_trans);

  const math::quat rotation = math::quat_init_with_axis_angle(0, 1, 0, turn);
  const math::quat new_rot  = math::quat_multiply(rotation, actor_trans.rotation);
  
  const math::transform new_transform = math::transform_init(actor_trans.position, actor_trans.scale, new_rot);
  
  Rigidbody::set_transform(Core::World{1}, e, new_transform);
}


void
move_forward(const Core::Entity e, const float fwd)
{
  //Rigidbody::apply_local_force(e, math::vec3_init(0, 0, fwd));
  
//  math::transform actor_trans;
//  Component::get(e, actor_trans);
//  
//  const math::vec3 movement = math::vec3_init(0, 0, fwd);
//  const math::vec3 rotated_movement = math::quat_rotate_point(actor_trans.rotation, movement);
//  
//  const math::vec3 position = math::vec3_add(actor_trans.position, rotated_movement);
//  
//  const math::transform new_transform = math::transform_init(position, actor_trans.scale, actor_trans.rotation);
//  
//  Rigidbody::set_transform(e, new_transform);
}


void
jump(const Core::Entity e, const float jmp)
{
  util::log_error("Actor::jump not impl");
}


bool
get_view_matrix(const Core::Entity e, math::mat4 &out_view_mat)
{
  math::transform view_transform;
  const bool has_transform = Transform::get(Core::World{1}, e, view_transform);//Component::get(e, view_transform);
  assert(has_transform);
  
  
  
  return has_transform;
}


} // ns