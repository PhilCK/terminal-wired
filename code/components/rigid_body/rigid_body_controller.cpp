#include "rigid_body_controller.hpp"
#include <bullet_wrapper/world.hpp>
#include <bullet_wrapper/rigidbody.hpp>
#include <bullet_wrapper/collider.hpp>
#include <math/mat/mat4.hpp>
#include <math/transform/transform.hpp>
#include <LinearMath/btIDebugDraw.h>
#include <systems/debug_line_renderer/debug_line_renderer.hpp>
#include <utils/logging.hpp>
#include <map>
#include <core/world/world.hpp>
#include <systems/transform/transform_controller.hpp>
#include <systems/physics_world/physics_world_controller.hpp>


namespace
{
  std::map<Core::Entity, bullet::rigidbody> rigid_bodies;
  
  bullet::rigidbody
  create_rigid_body(const Rigidbody::Rigidbody_data &data, const math::transform &transform)
  {
    std::unique_ptr<btCollisionShape> collider;
  
    switch(data.collider.type)
    {
    case(Rigidbody::Collider_type::box):
      collider = bullet::create_cube_collider();
    break;
    
    case(Rigidbody::Collider_type::capsule):
        collider = bullet::create_capsule_collider();
    break;
    
    case(Rigidbody::Collider_type::sphere):
        assert(false); // this is a cube.
        collider = bullet::create_cube_collider();
    break;
    
    case(Rigidbody::Collider_type::static_plane):
        collider = bullet::create_static_plane_collider();
    break;
    
    default:
      assert(false); // Unkown type.
      util::log_error("Unkown collider type");
      collider = bullet::create_cube_collider();
    }
    
    const float x = math::vec3_get_x(transform.position);
    const float y = math::vec3_get_y(transform.position);
    const float z = math::vec3_get_z(transform.position);
    
    //auto ptr = new bullet::rigidbody(std::move(collider), x, y, z, data.mass, bullet::axis::y_axis);
    //return ptr;
    return bullet::rigidbody(std::move(collider), x, y, z, data.mass, bullet::axis::y_axis);
  } // create_rb
  
}


namespace Rigidbody {


void
apply_local_force(const Core::Entity e, const math::vec3 dir)
{
  assert(rigid_bodies.count(e));
  
  auto rb = rigid_bodies.at(e);
  rb.apply_local_force(btVector3(math::vec3_get_x(dir),
                                  math::vec3_get_y(dir),
                                  math::vec3_get_z(dir)));
}


void
apply_world_force(const Core::Entity e, const math::vec3 dir)
{
  //assert(rigid_bodies.count(e));
  if(!rigid_bodies.count(e))
  {
    return;
  }
  
  auto rb = rigid_bodies.at(e);
  rb.apply_world_force(btVector3(math::vec3_get_x(dir),
                                  math::vec3_get_y(dir),
                                  math::vec3_get_z(dir)));
}


void
set_scale(const Core::Entity e, const math::vec3 scale)
{
  if(!rigid_bodies.count(e))
  {
    return;
  }
  
  auto rb = rigid_bodies.at(e);
  
  rb.set_collision_shape(bullet::create_cube_collider(
    math::vec3_get_x(scale) * 0.5f,
    math::vec3_get_y(scale) * 0.5f,
    math::vec3_get_z(scale) * 0.5f
  ));
}


void
apply_local_torque(const Core::Entity e, const math::vec3 dir)
{
  assert(rigid_bodies.count(e));
  
  auto rb = rigid_bodies.at(e);
  rb.apply_local_torque(btVector3(math::vec3_get_x(dir),
                                  math::vec3_get_y(dir),
                                  math::vec3_get_z(dir)));
}


void
set_transform(const Core::Entity e, const math::transform &trans)
{
  assert(rigid_bodies.count(e));
  
  // Convert rotation to bullet
  math::quat bt_friendly_rot;
  {
    //const math::quat rb_quat    = math::quat_init(quat_data.at(0), quat_data.at(1), quat_data.at(2), quat_data.at(3));
    const math::mat3 rot_mat    = math::quat_get_rotation_matrix(trans.rotation);
    const math::mat3 rot_mat_tr = math::mat3_get_transpose(rot_mat);
    bt_friendly_rot = math::quat_init_with_mat3(rot_mat_tr);
  }
  
  btTransform update_transform;
  update_transform.setOrigin(btVector3(math::vec3_get_x(trans.position),
                                       math::vec3_get_y(trans.position),
                                       math::vec3_get_z(trans.position)));

  update_transform.setRotation(btQuaternion(math::quat_get_x(bt_friendly_rot),
                                            math::quat_get_y(bt_friendly_rot),
                                            math::quat_get_z(bt_friendly_rot),
                                            math::quat_get_w(bt_friendly_rot)));
  
  auto &rb = rigid_bodies.at(e);
  rb.set_transform(update_transform);
}


void
set_gravity(const Core::Entity e, const math::vec3 dir)
{
  assert(rigid_bodies.count(e));
  
  auto &rb = rigid_bodies.at(e);
  rb.set_gravity(btVector3(math::vec3_get_x(dir), math::vec3_get_y(dir), math::vec3_get_z(dir)));
}


void
set_mass(const Core::Entity e, const float mass)
{
  assert(rigid_bodies.count(e));
  
  auto &rb = rigid_bodies.at(e);
  rb.set_mass(mass);
}


void
set_trigger(const Core::Entity e, const bool set_trigger)
{
  assert(rigid_bodies.count(e));
  
  auto &rb = rigid_bodies.at(e);
  rb.set_trigger(set_trigger);
}

} // ns


namespace comp {
namespace rigid_body_controller {


void
update_world(const float dt)
{
//  for(const auto &ent : map_rigid_bodies)
//  {
//    // Need to preserve scale
//    math::transform old_transform;
//    Component::get<math::transform>(ent.first, old_transform);
//    
//    //const math::mat4 world_rb = math::mat4_init_with_array(ent.second->get_world_matrix());
//    //const math::mat4 rot_mat  = math::mat4_id();// math::mat4_rotate_around_axis(math::vec3_init(0, 0, 1), math::half_tau());
//    //const math::mat4 corrected_mat = math::mat4_multiply(world_rb, rot_mat);
//    
//    const auto quat_data        = ent.second->get_rotation_quat();
//    const math::quat rb_quat    = math::quat_init(quat_data.at(0), quat_data.at(1), quat_data.at(2), quat_data.at(3));
//    const math::mat3 rot_mat    = math::quat_get_rotation_matrix(rb_quat);
//    const math::mat3 rot_mat_tr = math::mat3_get_transpose(rot_mat);
//    const math::quat rb_quat2   = math::quat_init_with_mat3(rot_mat_tr);
//    
//    const auto pos_data = ent.second->get_position();
//    const math::vec3 rb_pos = math::vec3_init_with_array(&pos_data[0]);
//    
//    //math::transform from_rb       = math::transform_init_from_world_matrix(world_rb);
//    //math::transform from_rb = math::transform_init_from_world_matrix(corrected_mat);
//    
//    math::transform from_rb;
//    from_rb.rotation = rb_quat2;
//    from_rb.position = rb_pos;
//    from_rb.scale    = old_transform.scale;
//    
//    Component::set<math::transform>(ent.first, from_rb);
//  }

  for(const auto &ent : rigid_bodies)
  {
    // Need to preserve scale
    math::transform old_transform;
    //Component::get<math::transform>(ent.first, old_transform);
    Transform::get(Core::World{1}, ent.first, old_transform);
    
    //const math::mat4 world_rb = math::mat4_init_with_array(ent.second->get_world_matrix());
    //const math::mat4 rot_mat  = math::mat4_id();// math::mat4_rotate_around_axis(math::vec3_init(0, 0, 1), math::half_tau());
    //const math::mat4 corrected_mat = math::mat4_multiply(world_rb, rot_mat);
    
    const auto quat_data        = ent.second.get_rotation_quat();
    const math::quat rb_quat    = math::quat_init(quat_data.at(0), quat_data.at(1), quat_data.at(2), quat_data.at(3));
    const math::mat3 rot_mat    = math::quat_get_rotation_matrix(rb_quat);
    const math::mat3 rot_mat_tr = math::mat3_get_transpose(rot_mat);
    const math::quat rb_quat2   = math::quat_init_with_mat3(rot_mat_tr);
    
    const auto pos_data = ent.second.get_position();
    const math::vec3 rb_pos = math::vec3_init_with_array(&pos_data[0]);
    
    //math::transform from_rb       = math::transform_init_from_world_matrix(world_rb);
    //math::transform from_rb = math::transform_init_from_world_matrix(corrected_mat);
    
    math::transform from_rb;
    from_rb.rotation = rb_quat2;
    from_rb.position = rb_pos;
    from_rb.scale    = old_transform.scale;
    
    Transform::set(Core::World{1}, ent.first, from_rb);
  }
}


} // namespace
} // namespace


namespace Component {


template<>
bool
add<Rigidbody::Rigidbody_data>(const Core::Entity e)
{
  Rigidbody::Rigidbody_data data;
  data.mass = 0;
  
  math::transform trans;
  assert(Component::get(e, trans));

  auto rb = create_rigid_body(data, trans);
  
  uint32_t id = (Core::entity_as_uint(e));
  
  std::size_t* ptr = nullptr;
  ptr = (std::size_t*)id;
  
  rb.set_user_pointer(ptr);
  
  rigid_bodies.insert(std::pair<Core::Entity, bullet::rigidbody>(e, rb));
  Sys::Physics_world::detail::get_world().add_rigidbody(rb);
  
  return true;
}


template<>
bool
get<Rigidbody::Rigidbody_data>(const Core::Entity e, Rigidbody::Rigidbody_data &get)
{
  return false;
}


template<>
bool
set<Rigidbody::Rigidbody_data>(const Core::Entity e, const Rigidbody::Rigidbody_data &set)
{
  math::transform trans;
  //assert(Component::get(e, trans));
  Transform::get(Core::World{1}, e, trans);
  

  auto rb = create_rigid_body(set, trans);
  
  uint32_t i = (Core::entity_as_uint(e));
  
  uint32_t* ptr = nullptr;
  ptr = (uint32_t*)i;
  
  rb.set_user_pointer(ptr);
  
  rigid_bodies.insert(std::pair<Core::Entity, bullet::rigidbody>(e, rb));
  Sys::Physics_world::detail::get_world().add_rigidbody(rb);
  
  return true;
}


} // ns