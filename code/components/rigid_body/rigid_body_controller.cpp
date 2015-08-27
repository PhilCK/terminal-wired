#include "rigid_body_controller.hpp"
#include <bullet_wrapper/world.hpp>
#include <bullet_wrapper/rigidbody.hpp>
#include <bullet_wrapper/collider.hpp>
#include <math/mat/mat4.hpp>
#include <math/transform/transform.hpp>
#include <components/transform/transform_controller.hpp>
#include <LinearMath/btIDebugDraw.h>
#include <systems/debug_line_renderer/debug_line_renderer.hpp>
#include <utils/logging.hpp>
#include <map>

#include <systems/physics_world/physics_world_controller.hpp>


namespace
{
  std::map<Core::Entity, bullet::rigidbody*> map_rigid_bodies;
  
  std::unique_ptr<bullet::rigidbody>
  create_rb(const Rigidbody::Rigidbody_data &data, const math::transform &transform)
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
    
    return std::make_unique<bullet::rigidbody>(std::move(collider), x, y, z, data.mass, bullet::axis::y_axis);
  } // create_rb
}


namespace Rigidbody {


void
apply_local_force(const Core::Entity e, const math::vec3 dir)
{
  assert(map_rigid_bodies.count(e));
  
  auto rb = map_rigid_bodies.at(e);
  rb->apply_local_force(math::vec3_get_x(dir), math::vec3_get_y(dir), math::vec3_get_z(dir));
}


void
apply_local_torque(const Core::Entity e, const math::vec3 dir)
{
  assert(map_rigid_bodies.count(e));
  
  auto rb = map_rigid_bodies.at(e);
  rb->apply_local_torque(math::vec3_get_x(dir), math::vec3_get_y(dir), math::vec3_get_z(dir));
}


} // ns


namespace comp {
namespace rigid_body_controller {


void
update_world(const float dt)
{
  for(const auto &ent : map_rigid_bodies)
  {
    // Need to preserve scale
    math::transform old_transform;
    Component::get<math::transform>(ent.first, old_transform);
    
    const math::mat4 world_rb     = math::mat4_init_with_array(ent.second->get_world_matrix());
    math::transform from_rb       = math::transform_init_from_world_matrix(world_rb);
    from_rb.scale = old_transform.scale;
    
    Component::set<math::transform>(ent.first, from_rb);
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

  auto rb = create_rb(data, trans);
  
  map_rigid_bodies.insert(std::pair<Core::Entity, bullet::rigidbody*>(e, rb.get()));
  Sys::Physics_world::detail::get_world().add_rigidbody(std::move(rb));
  
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
  assert(Component::get(e, trans));

  auto rb = create_rb(set, trans);
  //auto rb_ptr = std::make_unique<bullet::rigidbody>(rb);
  
  map_rigid_bodies.insert(std::pair<Core::Entity, bullet::rigidbody*>(e, rb.get()));
  Sys::Physics_world::detail::get_world().add_rigidbody(std::move(rb));
  
  return true;
}


} // ns
