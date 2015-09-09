#include <systems/script/script_manager.hpp>
#include "script_controller.hpp"
#include "script.hpp"
#include <map>



namespace
{
  Sys::Script::Script_manager script_mgr;
}


namespace Component {


template<>
bool
add<Script_component>(const Core::Entity e)
{
  return script_mgr.add_script(e, "");
}


template<>
bool
set<Script_component>(const Core::Entity e, const Script_component &component)
{
  return script_mgr.add_script(e, component.get_code());
}


template<>
bool
get<Script_component>(const Core::Entity e, Script_component &component)
{
  // Get code and return it.
  return true;
}


} // namespace