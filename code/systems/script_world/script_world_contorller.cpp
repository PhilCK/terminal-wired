#include <core/event/event.hpp>
#include <systems/script_world/script_world_controller.hpp>
#include <systems/script_world/script_world_manager.hpp>
#include <systems/script_world/detail/chai_instances.hpp>
#include <systems/script_world/detail/chai_binding.hpp>
#include <systems/physics_world/physics_world_controller.hpp>


namespace
{
  Sys::Script::Script_manager script_mgr;
}


namespace Sys {
namespace Script {


void
initialize()
{
  Script_detail::Chai_instances::initialize(/* instances */128);
  Script_detail::Chai_binding::initialize();
  
  Core::Event::add_callback(Physics_world::collision_event_id, event_callback);
}


Sys::Script::Script_manager&
get_current_script_mgr()
{
  return script_mgr;
}


bool
event_callback(const uint32_t id, const void *data)
{
  if(id == Sys::Physics_world::collision_event_id)
  {
    assert(data);
  
    const Physics_world::Collision_event *event = static_cast<const Physics_world::Collision_event*>(data);
    
    get_current_script_mgr().schedule_collision_callback(event->entity_a, event->entity_b);
  }
  
  return false;
}


} // ns
} // ns