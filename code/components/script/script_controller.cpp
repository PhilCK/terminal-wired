#include <systems/script/script_engine.hpp>
#include <systems/physics_world/physics_world_controller.hpp>
#include "script_controller.hpp"
#include "script.hpp"
#include <map>


namespace
{
  std::map<Core::Entity, Script::Script_data> scripts;
}


namespace Script
{


bool collision_callback(const uint32_t id, const void* data)
{
  const auto collision_data = static_cast<const Sys::Physics_world::Collision_event*>(data);
  
  // Do we have collision_data a?
  Script_data script;
  if(Component::get(collision_data->entity_a, script))
  {
    script.call_contact_hook(collision_data->entity_b);
  }
  

  return true;
}


void
reset(const Core::Entity e)
{
  scripts[e] = Script::Script_data(e);
}

void
on_throw(const Core::Entity e)
{
  scripts[e].call_thrown_hook();
}

}


namespace Component {


template<>
bool
add<Script::Script_data>(const Core::Entity e)
{
  scripts.emplace(std::pair<Core::Entity, Script::Script_data>(e, Script::Script_data(e)));

  return true;
}


template<>
bool
set<Script::Script_data>(const Core::Entity e, const Script::Script_data &component)
{
  scripts[e] = component;
  
  return true;
}


template<>
bool
get<Script::Script_data>(const Core::Entity e, Script::Script_data &component)
{
  component = scripts[e];

  return true;
}


} // namespace