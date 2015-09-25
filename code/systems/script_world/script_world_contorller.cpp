#include <core/event/event.hpp>
#include <common/event_ids.hpp>
#include <systems/script_world/script_world_controller.hpp>
#include <systems/script_world/script_world_manager.hpp>
#include <systems/script_world/detail/chai_instances.hpp>
#include <systems/script_world/detail/chai_binding.hpp>
#include <systems/physics/physics_world_controller.hpp>


namespace
{
  Sys::Script::Script_manager script_mgr;
}


namespace Script {


void
initialize()
{
  Script_detail::Chai_instances::initialize(/* instances */128);
  Script_detail::Chai_binding::initialize();
  
  Core::Event::add_callback(Common::Event_ids::physics_collision, event_callback);
  Core::Event::add_callback(Core::Event_id::entity_destroy, event_callback);
}


Sys::Script::Script_manager&
get_current_script_mgr()
{
  return script_mgr;
}


bool
event_callback(const uint32_t id, const void *data)
{
  switch(id)
  {
    case(Common::Event_ids::physics_collision):
    {
      assert(data);
    
      const Physics_world::Collision_event_data *event = static_cast<const Physics_world::Collision_event_data*>(data);
      
      get_current_script_mgr().schedule_collision_callback(event->entity_a, event->entity_b);
      break;
    }
    
    case(Core::Event_id::entity_destroy):
    {
      assert(data);
      
      const Core::Destroy_entity_event *event = static_cast<const Core::Destroy_entity_event*>(data);
      
      get_current_script_mgr().remove_script(event->e);
      break;
    }
  }
  
  return false;
}



bool
add(const Core::World w, const Core::Entity e, const std::string &code)
{
  script_mgr.add_script(e, code);
  
  return true;
}


bool
remove(const Core::World w, const Core::Entity e)
{
  script_mgr.remove_script(e);
  
  return true;
}


} // ns