#include "rigid_body_controller.hpp"
#include <bullet_wrapper/world.hpp>
#include <bullet_wrapper/rigidbody.hpp>
#include <math/mat/mat4.hpp>
#include <math/transform/transform.hpp>
#include <components/transform/transform_controller.hpp>
#include <LinearMath/btIDebugDraw.h>
#include <systems/debug_line_renderer/debug_line_renderer.hpp>
#include <utils/logging.hpp>
#include <map>


namespace
{
  std::map<Core::Entity, bullet::rigidbody*> rigidbodies;
  bullet::world world;
  
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
  
  world.add_rigidbody(std::move(rb));
  
  
  if(!is_set)
  {
    world.get_world()->setDebugDrawer(&debug_draw);
    is_set = true;
  }
}


bullet::world&
get_world()
{
  return world;
}


void
update_world(const float dt)
{
  world.update_world(dt);
  world.get_world()->debugDrawWorld();
  
  // Update transforms
  for(const auto &ent : rigidbodies)
  {
    const math::mat4 world_rb     = math::mat4_init_with_array(ent.second->get_world_matrix());
    const math::transform from_rb = math::transform_init_from_world_matrix(world_rb);
    Component::set<math::transform>(ent.first, from_rb);
  }

}


} // namespace
} // namespace