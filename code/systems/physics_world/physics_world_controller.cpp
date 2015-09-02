#include <systems/physics_world/physics_world_controller.hpp>
#include <systems/debug_line_renderer/debug_line_renderer.hpp>
#include <core/event/event.hpp>
#include <utils/logging.hpp>
#include <string>
#include <new>


namespace
{
  bullet::world phy_world;
  
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
}


namespace Sys {
namespace Physics_world {


void
initialize()
{
  phy_world.get_world()->setDebugDrawer(&debug_draw);
}


void
update_world(const float dt)
{
  Sys::Physics_world::detail::get_world().update_world(dt);
  Sys::Physics_world::detail::get_world().get_world()->debugDrawWorld();
  
  const auto collisions = Sys::Physics_world::detail::get_world().check_collisions();
  
  for(const auto &coll : collisions)
  {
    // Convert user pointers to entities.
    const std::size_t enta_id = (std::size_t)coll.usr_ptr_a;
    const Core::Entity ent_a = Core::uint_as_entity(static_cast<uint32_t>(enta_id));

    const std::size_t entb_id = (std::size_t)coll.usr_ptr_b;
    const Core::Entity ent_b = Core::uint_as_entity(static_cast<uint32_t>(entb_id));
    
    // Get some data from the event queue.
    void* data_loc = Core::Event::add_event_to_queue(collision_event_id, sizeof(Collision_event));
    assert(data_loc);
    
    // Create event data.
    const Collision_event * evt = new(data_loc) Collision_event{ent_a, ent_b};
    assert(evt);
  }
}


std::array<float, 3>
get_gravity()
{
  return {1,2,3};
}


void
set_gravity(const std::array<float, 3> &set_gravity)
{
  
}


namespace detail {

bullet::world&
get_world()
{
  return phy_world;
}

}

} // ns
} // ns