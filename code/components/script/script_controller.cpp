#include <components/script/script_controller.hpp>
#include <systems/script/script_manager.hpp>
#include <systems/script/script_controller.hpp>
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


template<>
bool
get<Script_component>(const Core::Entity e, Script_component &component)
{
  // Get code and return it.
  return true;
}


} // namespace