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
  std::map<Core::Entity, bullet::rigidbody*> rigidbodies;
  
  class Debug_draw : public btIDebugDraw
  {
  public:
  
    void
    drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color) override
    {
      Sys::Debug_line_renderer::add_line({from.x(), from.y(), from.z()}, {to.x(), to.y(), to.z()}, {color.x(), color.y(), color.z()});
    }
    
    void
    drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color) override
    {
      
    }

    void
    reportErrorWarning(const char* warning_string) override
    {
      const std::string error_msg = warning_string;
      util::log_error("Bullet: " + error_msg);
    }
    
    void
    draw3dText(const btVector3 &location, const char *textString) override {}
    
    void
    setDebugMode(int debugMode) override
    {
      m_debugMode = debugMode;
    }
    
    int
    getDebugMode() const override
    {
      return m_debugMode;
    }
	
  private:

    int m_debugMode = btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawContactPoints;

  
  }; // class
  
  Debug_draw debug_draw;
  bool is_set = false;
}


namespace comp {
namespace rigid_body_controller {


void
add(const Core::Entity add_rigid_body)
{
  
}


void
set(const Core::Entity set_rigid_body, bullet::rigidbody new_rigid_body)
{
  auto rb = std::make_unique<bullet::rigidbody>(std::move(new_rigid_body));

  rigidbodies.emplace(std::pair<Core::Entity, bullet::rigidbody*>(set_rigid_body, rb.get()));
  
  Physics_world::detail::get_world().add_rigidbody(std::move(rb));
  
  
  if(!is_set)
  {
    Physics_world::detail::get_world().get_world()->setDebugDrawer(&debug_draw);
    is_set = true;
  }
}


bullet::world&
get_world()
{
  return Physics_world::detail::get_world();
}


void
update_world(const float dt)
{
  Physics_world::detail::get_world().update_world(dt);
  Physics_world::detail::get_world().get_world()->debugDrawWorld();
  
  // Update transforms
  for(const auto &ent : rigidbodies)
  {
    // Need to preserve scale
    math::transform old_transform;
    Component::get<math::transform>(ent.first, old_transform);
    
    const math::mat4 world_rb     = math::mat4_init_with_array(ent.second->get_world_matrix());
    math::transform from_rb = math::transform_init_from_world_matrix(world_rb);
    from_rb.scale = old_transform.scale;
    
    Component::set<math::transform>(ent.first, from_rb);
  }
}


} // namespace
} // namespace


namespace
{
  std::map<Core::Entity, bullet::rigidbody*> map_rigid_bodies;
  
  std::unique_ptr<bullet::rigidbody>
  create_rb(const Rigidbody::Rigidbody_data &data)
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
    
    return std::make_unique<bullet::rigidbody>(std::move(collider), 0, 0, 0, data.mass);
  } // create_rb
}


namespace Component {


template<>
bool
add<Rigidbody::Rigidbody_data>(const Core::Entity e)
{
  Rigidbody::Rigidbody_data data;
  data.mass = 0;
  
  auto rb = create_rb(data);
  //auto rb_ptr = std::make_unique<bullet::rigidbody>(rb);
  
  map_rigid_bodies.insert(std::pair<Core::Entity, bullet::rigidbody*>(e, rb.get()));
  Physics_world::detail::get_world().add_rigidbody(std::move(rb));
  
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
  auto rb = create_rb(set);
  //auto rb_ptr = std::make_unique<bullet::rigidbody>(rb);
  
  map_rigid_bodies.insert(std::pair<Core::Entity, bullet::rigidbody*>(e, rb.get()));
  Physics_world::detail::get_world().add_rigidbody(std::move(rb));
  
  return true;
}


} // ns
