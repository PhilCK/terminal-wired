#include <components/script/script_controller.hpp>
#include <systems/script_world/script_world_manager.hpp>
#include <systems/script_world/script_world_controller.hpp>
#include <map>


namespace Component {


template<>
bool
add<Script_component>(const Core::Entity e)
{
  return Sys::Script::get_current_script_mgr().add_script(e, "");
}


template<>
bool
set<Script_component>(const Core::Entity e, const Script_component &component)
{
  return Sys::Script::get_current_script_mgr().add_script(e, component.get_code());
}


} // namespace